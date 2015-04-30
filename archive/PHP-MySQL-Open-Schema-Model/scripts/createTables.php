<?php

$model = new Model('dummy');
$model->initialize('');
$tables = array(
    'system',
    'group',
    'dummy'
);
$dbSql = 'create database if not exists db322;
                use db322;';
$sql =
    'drop table if exists #tablename#;
    create table #tablename#(
      id int auto_increment primary key
      ,foreign_id int
      ,type varchar(255)
      ,created int
      ,modified int, unix int, date varchar(255)
      ,name text, status text
      ,description text
    );

    drop table if exists #tablename#_meta;
    create table #tablename#_meta(
      meta_id int auto_increment primary key
      ,meta_foreign_id int
      ,meta_key text
      ,meta_value text
    );';
$model->query($dbSql);
foreach ($tables as $table) {
    $createTable = str_replace('#tablename#', $table, $sql);
    $model->query($createTable);
}