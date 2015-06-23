<?php

namespace ApplicationCommon\Db;

class DataCacheKey {
    public $key = '';
    public function __invoke($parameters) {
        return $this->hash($parameters);
    }
    public static function hash($key) {
        return json_encode($key);
    }
    public function __construct($key = null) {
        if ($key === null) {
            $key = uniqid('_');
        } else {
            $key = $this->__invoke($key);
        }
        $this->key = $key;
    }
    public function __toString() {
        return $this->key;
    }
}