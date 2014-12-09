<?php

namespace AR\Db;
use Zend\Db\ResultSet\ResultSet;

class DataResultSet extends ResultSet {
    /**
     * handles MSSQL error which returns -1 for rows affected if data not available, leading to negative counts -_-
     * warning: this uses up the iterator and ZF2 buffering does not seem to work, but at least it raises an exception
     * @return int
     */
    public function count() {
        $this->count = parent::count();
        if ($this->count < 0) {
            $this->count = count($this->toArray());
        }
        return $this->count;
    }

    // todo return array with selectable array key
//    public function toArray() {
//
//    }
}
