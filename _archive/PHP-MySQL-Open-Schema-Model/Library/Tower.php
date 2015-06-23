<?php

class Tower
{
    public $models = array();
    private static $_models;

    public static function model($name, $useObjectMode = true) {
        $t = 'Model_'.ucfirst($name);
        if (!isset(self::$_models[$t]) || self::$_models[$t]->objectMode != $useObjectMode) {
            self::$_models[$t] = new Model($t, $useObjectMode);
        }
        return self::$_models[$t];
    }

    public static function dataObject($data, $class) {
        $class = ucfirst('Object_'.$class);
        return new $class($data);
    }

    public static function models($tables) {
        if (!is_array($tables)) {
            $tables = array($tables);
        }
        $models = array();
        foreach ($tables as $table) {
            $table = lcfirst($table);
            $models[$table] = Tower::model(ucwords($table));
        }
        return $models;
    }
}