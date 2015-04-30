<?php

class DataObject { //extend stdClass to avoid IDE complaints
    public $id;
    public $name;
    public $type;
    public $unix;
    public $date;
    public $modified;
    public $created;
    public $description;
    public $status;
    public $foreign_id;
    public $meta = array();

    public function __construct($data, $model = 'dummy') {
        foreach ($data as $key => $value) {
            $this->$key = $value;
        }
        $this->model = $model;
        return $this;
    }
    public function __get($key) {
        return $this->meta[$key];
    }
    public function __set($key, $val) {
        return $this->meta[$key] = $val;
    }
    public function save() {
        Tower::model($this->model)->set($this->out());
        return $this;
    }
    public function out() {
//        return json_decode(json_encode($this), true);
        return array(
            'id' => $this->id ?: null,
            'name' => $this->name,
            'type' => $this->type,
            'unix' => $this->unix,
            'date' => $this->date,
            'modified' => $this->modified,
            'created' => $this->created,
            'description' => $this->description,
            'status' => $this->status,
            'foreign_id' => $this->foreign_id,
            'meta' => $this->meta
        );
    }
}
