<?php

namespace ApplicationCommon\Db;

/**
 * Class DataCache
 * @package ApplicationCommon\Db
 * todo add zend adapter (?)
 *
 * Provides a standard cache interface for ActiveRecord and its DataMapper
 * Perhaps we could link a memory cache to this if needed, but for now it just tries to prevent redundant
 * select statements. Although SQLSRV has its own cache, this appears to be somewhat faster.
 */
class DataCache {
    public static $cache = array();

    public static function add($value) {
        return static::set(null, $value);
    }
    public static function debug(array $arr) {
//        if (strpos($arr[1], 'customers') !== false) {
//            _echo($arr, 1);
//        }
    }
    public static function clear($key = null) {
        if (($key === null || !is_string($key)) && !($key instanceof DataCacheKey)) {
            $key = new DataCacheKey($key);
        }
//        static::debug(array('cooling', $key . ''));
        unset(static::$cache[$key . '']);
        return $key;
    }
    public static function set($key = null, $value) {
        if (($key === null || !is_string($key)) && !($key instanceof DataCacheKey)) {
            $key = new DataCacheKey($key);
        }
//        static::debug(array('warming', $key . '', get_class($value)));
        static::$cache[$key . ''] = $value;
        return $key;
    }
    public static function get($key, callable $lambda = null) {
        if (($key === null || !is_string($key)) && !($key instanceof DataCacheKey)) {
            $key = new DataCacheKey($key);
        }
        $value = static::$cache[$key . ''];
        if ($value === null) {
//            static::debug(array('cold', $key . ''));
            if ($lambda !== null) {
                static::set($key . '', $lambda());
            }
        } else {
//            static::debug(array('hot', $key . '', get_class($value)));
        }
        return $value;
    }
}