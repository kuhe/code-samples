<?php

class DBH
{
    public static $dbh;
    public function __construct() {
        return DBH::dbh();
    }
    public static function dbh() {
        if (static::$dbh == null) {
            static::$dbh = new PDO(
                "mysql:host=".Zend_Registry::get('config')->resources->db->params->host.
                ";dbname=".Zend_Registry::get('config')->resources->db->params->dbname,
                Zend_Registry::get('config')->resources->db->params->username,
                Zend_Registry::get('config')->resources->db->params->password
                // or however you'd get the credentials
            );
        }
//        Zend_Registry::set('dbh_object', static::$dbh);
        return static::$dbh;
    }
}