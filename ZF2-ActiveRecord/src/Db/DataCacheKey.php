<?php

namespace AR\Db;

class DataCacheKey {
    public $key = '';
    public function __invoke($parameters) {
        return json_encode($parameters);
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