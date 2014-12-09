<?php

namespace AR\Model;

use AR\Db\DataMapper;
use Exception;
use Zend\Db\Adapter;
use Zend\Db\ResultSet\ResultSet;
use Zend\ServiceManager\ServiceLocatorInterface;
use Zend\Db\Sql\Update;
use Zend\Db\Sql\Insert;
use Zend\Db\Sql\Delete;
use Zend\Db\TableGateway\TableGateway;
use ReflectionObject;
use ReflectionProperty;
use AR\Db\DataResultSet;
use AR\Db\DataCache;
use AR\Db\DataCacheKey;

/**
 * Class DataObject
 * @package AR\Model
 *
 * Specify the adapter service name and table name in child classes.
 * Classes derived from this are intended to provide instantiation for a generic and extensible object representation of a table row.
 *
 * This type represents a domain business logic object while internalizing access to the table gateway and ORM.
 * Method calls will automatically read from cached instances in DataMapper in which the table gateway, adapter, and
 * result set prototype are already set.
 * CRUD operation is therefore available to the object itself, along with any logical manipulations you may add.
 *
 * This approximately follows the active record pattern but does not utilize ZF's row gateway.
 * Why? I don't know. I probably should have read the documentation.
 *
 * Read operations are static.
 * DataObject::get() provides the basis for read operations utilizing the internal adapter and gateway, and returns object(s)
 * of the derived class calling the method, or ResultSet objects iterable over the same.
 *
 * Write operations are non-static.
 * $dataObjectInstance->save() provides upsert operations while $dataObjectInstance->delete() provides deletion.
 * Write operations can act on the object itself or a passed in object/array.
 *
 * Additional utilities are the toArray(), toJson(), and ingest() methods.
 *
 * Usage in controllers:
 *
 * // class Giraffe extends DataObject { ... }
 * // there is a giraffe table in the zoo database so the class will define the table name and adapter service name
 * // inject service locator statically or with the first instantiation
 * DataObject::setServiceLocator($serviceLocator);
 *
 * $giraffe = Giraffe::get(1); // returns Giraffe instance representing row with key 1
 * $giraffe->name = 'Bob';
 * $giraffe->save(); // writes to DB, and you're done
 *
 */
abstract class DataObject {

    /**
     * @var string, required in any child class
     */
    protected $adapterServiceName = '';

    /**
     * @var string, required in any child class
     */
    protected $tableName = '';

    /**
     * @var \AR\Db\DataMapper
     */
    protected $mapper;
    protected static $serviceLocator;
    protected $protectedProperties = array();
    /**
     * @var string|string[], required in any child class that has a different id field name
     */
    protected $key = 'id';
    protected $columns = array();
    protected static $instances;

    const STATUS_ACTIVE = 1;
    const STATUS_DRAFT = 2;
    const STATUS_INACTIVE = 0;

    /**
     * @return static
     * Provides singleton, but only as needed by the static read methods, which utilize the DataMapper partner object
     * A local call will produce the last used Class
     * @throws Exception
     */
    public static function instance() {
        $class = get_called_class();
        if (!static::$instances[$class] instanceof static) {
            static::$instances[$class] = new static();
        }
        return static::$instances[$class];
    }

    /**
     * @param null $id
     * @param bool $initialize
     * @throws Exception
     * set $initialize to false to just get a shell. Used for setting result set prototypes.
     */
    public function __construct($id = null, $initialize = true) {
        if (!is_array($this->key)) {
            $this->key = array($this->key);
        }
        if (is_numeric($id)) {
            $this->initialize();
            $this->ingest(static::get($id));
        } else {
            $initialize && $this->initialize();
        }
    }

    public static function getServiceLocator() {
        return DataObject::$serviceLocator;
    }
    public static function setServiceLocator($sl) {
        DataObject::$serviceLocator = $sl;
    }

    /**
     * @throws \Exception
     *
     * todo remove service locator dependency
     */
    public function initialize() {
        static::$instances[get_called_class()] = $this;
        $serviceLocator = static::getServiceLocator();
        if (!$serviceLocator) throw new Exception('service locator not provided yet');
        if (!$this->adapterServiceName) throw new Exception(__CLASS__.' must define adapter service name');
        if (!$this->tableName) throw new Exception(__CLASS__.' must define table name');
        $this->mapper = DataMapper::instance(DataMapper::gateway($this, $serviceLocator), $this);
        $this->mapper->key = $this->key;
    }

    public function exchangeArray($data) {
        foreach ($data ?: array() as $key => $value) {
            if ($key) {
                $set = 'set' . ucfirst($key);
                // $this->$set($this->getDataValue($data, $key), $value);
                $this->$set($data[$key], $value);
            }
        }
    }

    /**
     * @param $data
     * @return static
     * The object assumes the state of a passed in data object or array
     */
    public function ingest($data) {
        if ($data instanceof DataObject) $data = $data->toArray();
        $this->exchangeArray($data);
        return $this;
    }

    /**
     * @return array string list of public data fields
     */
    public function getFields() {
        $properties = (new ReflectionObject($this))->getProperties(ReflectionProperty::IS_PUBLIC);
        $fields = array();
        foreach ($properties as $property) $fields[] = $property->name;
        return $fields;
    }

    public function toArray() {
        $array = array();
        foreach ($this->getFields() as $field) {
            $array[$field] = $this->$field;
        }
        return $array;
    }

    public function getTimestamp() {
        return date('Y-m-d H:i:s');
    }

    public function toJson() {
        return json_encode($this->toArray());
    }

    /**
     * @return DataMapper
     * @throws Exception
     * Retrieves and caches the mapper if necessary
     */
    public function getMapper() {
        if (!($this->mapper instanceof DataMapper)) {
            $serviceLocator = static::getServiceLocator();
            if (!$serviceLocator) throw new Exception('service locator not provided yet');
            $this->mapper = DataMapper::instance(DataMapper::gateway($this, $serviceLocator), $this);
        }
        return $this->mapper;
    }

    /**
     * @param array $data
     * @param bool $updateOnly
     * @param bool $debugQuery
     * @return array|bool|mixed
     * @throws Exception
     * upserts the provided data, or in the absence of that, the object itself into the database
     * if the class defines a columns property only those columns will be used for insertion
     */
    public function save(array $data = array(), $updateOnly = false, $debugQuery = false) {
        $data = !empty($data) ? $data : $this->toArray();

        if (!empty($this->columns)) {
            foreach ($data as $key => $value) {
                if (!in_array($key, $this->columns)) unset($data[$key]);
            }
        }

        $compound = count($this->key) > 1;

        $update = true;
        $restriction = array();
        foreach ($this->key as $keyName) {
            if (!isset($this->$keyName) || $this->$keyName === '') {
                if ($compound) {
                    throw new Exception('compound key missing element '. $keyName);
                }
                $update = false;
            } else {
                if (!$compound && $update && !is_numeric($keyName)) {
                    $update = static::getOne(array($keyName => $this->$keyName)) instanceof static;
                }
            }
            $restriction[$keyName] = $this->$keyName;
            if (!$compound && (is_numeric($keyName) || (!isset($this->$keyName) || $this->$keyName === ''))) {
                unset($data[$keyName]);
            }
        }
        if ($compound) {
            $update = static::getOne($restriction) instanceof static;
        }
        if ($update) {
            $update = (new Update($this->getMapper()->getTableGateway()->getTable()))->set($data)->where($restriction);
            $this->mapper->trace[] = __METHOD__;
            $this->mapper->log($update, $data);
            if ($debugQuery) {
                return end(DataMapper::$queriesLog);
            }
            $this->mapper->getTableGateway()->updateWith($update);
//            DataCache::set(
//                new DataCacheKey(array($this->getMapper()->getTableGateway()->getTable() => $data[$this->key[0]])),
//                $this->ingest($data)
//            );
            if ($compound) {
                return $restriction;
            } else {
                $keyIndex = $this->key[0];
                return $this->$keyIndex;
            }
        } else if (!$updateOnly) {
            if (!$compound) {
                if (is_numeric($data[$this->key[0]])) {
                    unset($data[$this->key[0]]);
                }
            }
            $insert = (new Insert($this->getMapper()->getTableGateway()->getTable()))->values($data);
            $this->mapper->trace[] = __METHOD__;
            $this->mapper->log($insert, $data);
            if ($debugQuery) {
                return end(DataMapper::$queriesLog);
            }
            $this->mapper->getTableGateway()->insertWith($insert);
            $identity = $this->mapper->getInsertIdentity();
//            DataCache::set(
//                new DataCacheKey(array($this->getMapper()->getTableGateway()->getTable() => $identity)),
//                $this->ingest($data)
//            );
            if ($compound) {
                return $restriction;
            } else {
                $keyIndex = $this->key[0];
                $this->$keyIndex = $identity;
                return $identity;
            }
        }
        return false;
    }

    /*
     * same as save but does not attempt to insert
     */
    public function update(array $data = array(), $upsert = false, $debugQuery = false) {
        $this->getMapper()->trace[] = __METHOD__;
        if ($upsert) {
            return $this->save($data, false, $debugQuery);
        } else {
            return $this->save($data, true, $debugQuery);
        }
    }

    /*
     * same as save but only attempts to insert
     */
    public function add(array $data = array(), $debugQuery = false) {
        $this->getMapper()->trace[] = __METHOD__;
        $data = !empty($data) ? $data : $this->toArray();
        if (count($this->key) == 1) {
            $key = $this->key[0];
            unset($data[$key]);
            unset($this->$key);
        }
        return $this->save($data, false, $debugQuery);
    }

    /**
     * @param null|array|int $mixed
     * @param bool $debugQuery
     * @return int rows affected
     * @throws Exception
     */
    public function delete($mixed = null, $debugQuery = false) {
        $delete = new Delete($this->getMapper()->getTableGateway()->getTable());
        if (is_numeric($mixed)) {
            $id = floor($mixed);
            $delete->where(array($this->key[0] => $id));
        } else if (is_array($mixed)) {
            $delete->where($mixed);
        } else {
            $restriction = array();
            foreach ($this->key as $keyName) {
                if (!isset($this->$keyName)) {
                    throw new Exception('improperly qualified deletion');
                }
                $restriction[$keyName] = $this->$keyName;
            }
            $delete->where($restriction);
        }
        $this->mapper->trace[] = __METHOD__;
        $this->mapper->log($delete, $mixed);
        if ($debugQuery) {
            return end(DataMapper::$queriesLog);
        }
        $affectedRowCount = $this->mapper->getTableGateway()->deleteWith($delete);
        return $affectedRowCount;
    }

    /**
     * @param array $parameters
     * @param bool $debugQuery
     * @return int rows affected
     * @throws Exception
     */
    public static function remove(array $parameters, $debugQuery = false) {
        if (empty($parameters)) throw new Exception('unqualified deletion');
        return static::instance()->delete($parameters, $debugQuery);
    }

    /**
     * @param array|int $params id or where clause(s)
     * @param int $limit
     * @return static|DataResultSet[static]
     * @throws Exception
     */
    public static function get($params = null, $limit = null, $debugQuery = false) {
        static::instance()->getMapper()->setColumns(static::instance()->columns);
        return static::instance()->getMapper()->get($params, $limit, $debugQuery);
    }

    /**
     * @param array|int $params id or where clause(s)
     * @return static
     * @throws Exception
     */
    public static function getOne($params = null, $debugQuery = false) {
        static::instance()->getMapper()->setColumns(static::instance()->columns);
        return static::instance()->getMapper()->getOne($params, $debugQuery);
    }

}
