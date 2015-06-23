<?php

namespace ApplicationCommon\Db;

use Zend\Db\Sql\Where;
use Zend\Db\Sql\Predicate;
use Zend\Db\Sql\SqlInterface;
use Zend\Db\TableGateway\AbstractTableGateway;
use Zend\Db\Sql\Select;
use ApplicationCommon\Db\TableGateway\ReadOnlyReadyTableGateway;
use ApplicationCommon\Model\DataObject;
use Zend\Di\ServiceLocatorInterface;
use Zend\ServiceManager\ServiceManager;

/**
 * Class DataMapper
 * @package ApplicationCommon\Db
 * provides read operations and table gateway internalization for ApplicationCommon\Db\DataObject
 */
class DataMapper extends BaseMapper {

    protected $tableGateway;
    public $key = 'id';
    public $services;
    protected $columns = array();
    public function setColumns(array $columns) {
        $this->columns = $columns;
    }

    public static $mappers = array();
    public static $gateways = array();
    public static $queriesLog = array();

    public $detailedLogging = false;
    public $trace = array();

    public function __construct(AbstractTableGateway $tableGateway) {
        $this->tableGateway = $tableGateway;
    }

    public static function instance(AbstractTableGateway $tableGateway, DataObject $prototype) {
        $class = get_class($prototype);
        return static::$mappers[$class] ?: (static::$mappers[$class] = new DataMapper($tableGateway));
    }

    /**
     * @param DataObject $object
     * @param ServiceLocatorInterface|ServiceManager $serviceLocator
     * @return ReadOnlyReadyTableGateway
     */
    public static function gateway(DataObject $object, $serviceLocator) {
        if (static::$gateways[get_class($object)]) {
            return static::$gateways[get_class($object)];
        }
        $dbAdapter = $serviceLocator->get($object->getAdapterServiceName());
        $instance = get_class($object);
        $resultSetPrototype = new DataResultSet(DataResultSet::TYPE_ARRAYOBJECT, new $instance(null, false));
        $gateway = new ReadOnlyReadyTableGateway($object->getTableName(), $dbAdapter, null, $resultSetPrototype);
        return static::$gateways[get_class($object)] = $gateway;
    }

    /**
     * @param int|null|Where|\Closure|string|array|Predicate\PredicateInterface $mixed
     * @param $limit integer
     * @param $debugQuery bool return the sql string
     * @param array $join
     * @return DataResultSet<\ApplicationCommon\Model\DataObject>|DataObject
     * @throws \Exception
     */
    public function get($mixed = null, $limit = null, $debugQuery = false, array $join = array()) {
        if (is_numeric($mixed)) {
            $id = floor($mixed);
            $select = new Select($this->tableGateway->getTable());
            $select->where(array($this->key[0] => $id));
        } else if ($mixed === null) {
            $select = (new Select($this->tableGateway->getTable()))->order($this->tableGateway->getTable().'.'.$this->key[0].' desc');
        } else {
            $select = (new Select($this->tableGateway->getTable()))->order($this->tableGateway->getTable().'.'.$this->key[0].' desc');
            $select->where($mixed);
        }
        if (!empty($join)) {
            $select->join($join['name'], $join['on'], $join['columns'], $join['type']);
        }
        if (!empty($this->columns)) {
            $select->columns($this->columns);
        }
        if ($limit) $select->quantifier('TOP '.$limit);
        $this->trace[] = __METHOD__;
        @$this->log($select, $mixed);
        if ($debugQuery) {
            return end(DataMapper::$queriesLog);
        }
        try {
            // return $this->getTableGateway()->selectWith($select)->current();
            if ($mixed && is_numeric($mixed)) {
                $cache = DataCache::get(new DataCacheKey(array($this->tableGateway->getTable() => (string) $mixed)));
                if ($cache instanceof static) {
                    $result = $cache;
                } else {
                    $result = $this->getTableGateway()->selectWith($select);
                }
                if ($result instanceof static) {
                    return DataCache::get(new DataCacheKey(array($this->tableGateway->getTable() => (string) $mixed)),
                        function() use ($result) {
                            return $result;
                        }
                    );
                } else {
                    return $result;
                }
            }
            return $this->getTableGateway()->selectWith($select);
        } catch (\Exception $e) {
            if (getenv('APPLICATION_ENV') == 'production') {
                return new DataResultSet();
            } else {
                _echo(DataMapper::$queriesLog);
                throw $e;
            }
        }
    }

    public function log(SqlInterface $query, $params = null) {
        $trace = $this->trace;
        if ($this->detailedLogging) {
            static::$queriesLog[] =
                array(
                    'trace' => $trace,
                    'params' => $params,
                    'sql' =>
                        $string = $query->getSqlString($this->getTableGateway()->adapter->getPlatform())
                );
        } else {
            static::$queriesLog[] = $string = $query->getSqlString($this->getTableGateway()->adapter->getPlatform());
        }

        $this->trace = array();
        return $string;
    }

    /**
     * @param mixed $mixed
     * @param $debugQuery bool return the sql string
     * @return \ApplicationCommon\Model\DataObject
     */
    public function getOne($mixed = null, $debugQuery = false) {
        $this->trace[] = __METHOD__;
        if (is_array($mixed) && count($mixed) == 1 && current(array_keys($mixed)) == $this->key[0]) {
            $cache = DataCache::get(new DataCacheKey(array($this->tableGateway->getTable() => (string) current($mixed))));
            if ($cache instanceof static) {
                $result = $cache;
            } else {
                $result = $this->get($mixed, 1, $debugQuery);
                if ($result instanceof DataResultSet) {
                    $result = $result->current();
                }
            }
            if ($result instanceof static) {
                return DataCache::get(new DataCacheKey(array($this->tableGateway->getTable() => (string) current($mixed))),
                    function() use ($result) {
                        return $result;
                    }
                );
            } else {
                return $result;
            }
        }
        if (($result = $this->get($mixed, 1, $debugQuery)) instanceof DataResultSet) {
            $response = $result->current();
        } else {
            $response = $result;
        }
        return $response;
    }

    public function getInsertIdentity($useDefaultMechanism = false) {
        if ($useDefaultMechanism) {
            return $this->getTableGateway()->adapter->getDriver()->getConnection()->resource->lastInsertId();
        } else {
            $adapter = $this->getTableGateway()->adapter;
            $results = $adapter->query('SELECT @@IDENTITY as Current_Identity', $adapter::QUERY_MODE_EXECUTE);
            return $results->current()->Current_Identity;
        }
    }

}
