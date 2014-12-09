<?php

namespace AR\Db;

class DataCache {
    public static $cache = array();

    public static function add($value) {
        return static::set(null, $value);
    }

    public static function set($key = null, $value) {
        if ($key === null || !is_string($key)) {
            $key = new DataCacheKey($key);
        }
//        _echo(array('warming', $key . ''));
        static::$cache[$key . ''] = $value;
        return $key;
    }
    public static function get($key, callable $lambda = null) {
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