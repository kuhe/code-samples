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
    public static function clear($key = null) {
        if (($key === null || !is_string($key)) && !($key instanceof DataCacheKey)) {
            $key = new DataCacheKey($key);
        }
//        _echo(array('invalidating', $key . ''));
        unset(static::$cache[$key . '']);
        return $key;
    }
    public static function set($key = null, $value) {
        if (($key === null || !is_string($key)) && !($key instanceof DataCacheKey)) {
            $key = new DataCacheKey($key);
        }
//        _echo(array('warming', $key . ''));
        static::$cache[$key . ''] = $value;
        return $key;
    }
    public static function get($key, callable $lambda = null) {
        if (($key === null || !is_string($key)) && !($key instanceof DataCacheKey)) {
            $key = new DataCacheKey($key);
        }
        if (static::$cache[$key . ''] === null && $lambda !== null) {
//            _echo(array('cold', $key . ''));
            $key = static::set($key . '', $lambda());
            return static::$cache[$key . ''];
        } else {
//            _echo(array('warm', $key . ''));
            return static::$cache[$key . ''];
        }
    }
}