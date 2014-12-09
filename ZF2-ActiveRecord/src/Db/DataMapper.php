<?php

namespace AR\Db;

use Zend\Db\Sql\AbstractSql;
use Zend\Db\Sql\Sql;
use Zend\Db\Sql\SqlInterface;
use Zend\Db\TableGateway\AbstractTableGateway;
use Zend\Db\Sql\Select;
use Zend\Db\TableGateway\TableGateway;
use AR\Model\DataObject;
use Zend\Di\ServiceLocatorInterface;
use Zend\ServiceManager\ServiceManager;
use Zend\ServiceManager\ServiceManagerAwareInterface;
use Zend\Db\Adapter\Adapter as DbAdapter;

/**
 * Class DataMapper
 * @package AR\Db
 * provides read operations and table gateway internalization for AR\Db\DataObject
 */
class DataMapper implements ServiceManagerAwareInterface {

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
     * @return TableGateway
     */
    public static function gateway(DataObject $object, $serviceLocator) {
        if (static::$gateways[get_class($object)]) {
            return static::$gateways[get_class($object)];
        }
        $dbAdapter = $serviceLocator->get($object->getAdapterServiceName());
        $instance = get_class($object);
        $resultSetPrototype = new DataResultSet(DataResultSet::TYPE_ARRAYOBJECT, new $instance(null, false));
        $gateway = new TableGateway($object->getTableName(), $dbAdapter, null, $resultSetPrototype);
        return static::$gateways[get_class($object)] = $gateway;
    }

    /**
     * @param null $mixed
     * @param $limit integer
     * @param $debugQuery bool return the sql string
     * @return \AR\Model\DataObject
     * @throws \Exception
     */
    public function get($mixed = null, $limit = null, $debugQuery = false) {
        if (is_numeric($mixed)) {
            $id = floor($mixed);
            $select = new Select($this->tableGateway->getTable());
            $select->where(array($this->key[0] => $id));
        } else if ($mixed === null) {
            $select = (new Select($this->tableGateway->getTable()))->order($this->key[0].' desc');
        } else {
            $select = (new Select($this->tableGateway->getTable()))->order($this->key[0].' desc');
            $select->where($mixed);
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
            if (is_numeric($mixed)) {
                return $this->getTableGateway()->selectWith($select)->current();
//            return DataCache::get(new DataCacheKey(array($this->tableGateway->getTable() => $mixed)),
//                function() use ($select) {
//                    return $this->getTableGateway()->selectWith($select)->current();
//                }
//            );
            }
            return $this->getTableGateway()->selectWith($select);
        } catch (\Exception $e) {
            _echo(DataMapper::$queriesLog);
            throw $e;
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
     * @return \AR\Model\DataObject
     */
    public function getOne($mixed = null, $debugQuery = false) {
        $this->trace[] = __METHOD__;
        return ($result = $this->get($mixed, 1, $debugQuery)) instanceof DataResultSet ? $result->current() : $result;
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

    public function getServiceManager() {
        return $this->serviceManager;
    }

    public function setServiceManager(ServiceManager $serviceManager) {
        $this->serviceManager = $serviceManager;
    }

    public function setDbAdapter($dbAdapter) {
        $this->dbAdapter = $dbAdapter;
    }

    public function getDbAdapter() {
        return $this->dbAdapter;
    }

    /**
     * @return TableGateWay
     */
    public function getTableGateway() {
        return $this->tableGateway;
    }

    public function setTableGateway(TableGateway $tableGateway) {
        $this->tableGateway = $tableGateway;
    }

}
