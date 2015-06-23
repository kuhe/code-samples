<?php
class Model
{
    public $_table;
    public $_meta;
    protected $_dbh;
    public $objectMode = true;

    public function dbh() {
//        return $this->_dbh = Zend_Registry::get('dbh_object');
        return $this->_dbh = DBH::dbh();
    }

    public function query($sql) {
        $query = $this->_dbh->prepare($sql);
        return $query->execute();
    }

    public function __construct($table, $useObjectMode = true) {
        $this->initialize($table);
        $this->$objectMode = $useObjectMode;
    }

    public function initialize($table)
    {
        $this->_table = $table;
        $this->_meta = $table.'_meta';
        $this->dbh();
        return $this;
    }
    public function save($post) {
        return $this->upsert($post);
    }
    public function upsert($post) {
        if (!isset($post['id'])) {
            return $this->add($post);
        } else {
            return $this->set($post);
        }
    }
    public function getOne($id) {
        $result = $this->get($id);
        return array_shift($result);
    }
    public function get($params = array(), $showQuery = false)
    {
        if (!is_array($params) && !empty($params)) {
            $id = $params;
            $params = array(
                'where' => array(
                    'id' => $id
                )
            );
        }
        $cpost = array();
        $n = $inClauseCounter = 0;
        foreach ($params['where'] ?: array() as $k => $v) {
            if (!is_array($v)) {
                $cpost[':'.$k] = $v;
            } else {
                foreach ($v as $val) {
                    $cpost[':inClause'.$inClauseCounter] = $val;
                    $inClauseCounter++;
                }
            }
        }
        $query = 'select * from ';
        if ($params['withoutMeta']) {
            $query .= $this->_table.' ';
        } else {
            $query .= $this->_table.' left join '.$this->_meta.' on id = meta_foreign_id ';
        }

        $query .= $params['where'] ? 'where ' : '';
        $firstClause = true;
        foreach ($params['where'] ?: array() as $k => $v) {
            if (!is_array($v)) {
                $whereClause = ' = :'.$k;
            } else {
                $inSubClause = array();
                foreach ($v as $val) {
                    $inSubClause[] = ':inClause'.$n;
                    $n++;
                }
                $whereClause = ' in ('.implode(',',$inSubClause).')';
            }
            $query .= (!$firstClause ? ' and ' : '').$k.$whereClause;
            $firstClause = false;
        }

        if (isset($params['order'])) {
            $query .= ' order by '.$params['order'].' ';
        }

        if (isset($params['limit'])) {
            $query .= ' limit '.$params['limit'];
        }

        if ($showQuery) return $query;

        $statement = $this->_dbh->prepare($query);
        $statement->execute($cpost);

        $all = $statement->fetchAll(PDO::FETCH_ASSOC);

        $data = array();

        if (!$params['withoutMeta']) {
            foreach ($all as $k => $v) {
                if (!isset($data[$v['id']])) $data[$v['id']] = is_string($v) && substr($v, 0, 2) == 'a:' ? unserialize($v) : $v;
                if ($v['meta_key']) {
                    $data[$v['id']]['meta'][$v['meta_key']] = substr($v['meta_value'], 0, 2) == 'a:' ? unserialize($v['meta_value']) : $v['meta_value'];
                }
            }
            foreach ($data as $k => $datum) {
                unset($data[$k]['meta_id']);
                unset($data[$k]['meta_foreign_id']);
                unset($data[$k]['meta_key']);
                unset($data[$k]['meta_value']);
                ksort($data[$k]['meta']);
            }
        }

        if (isset($params['slice'])) {
            return array_slice($data, 0, $params['slice']);
        }

        if ($this->objectMode || $params['asObject']) {
            foreach ($data as $key => $item) {
                $data[$key] = Tower::dataObject($item, $this->_table);
            }
        }

        return $data;
    }
    public function add(array $post, array $meta = null)
    {
        unset($post['id']);
        if ($post['meta']) {
            $meta = $post['meta'];
            unset($post['meta']);
        }
        $post['created'] = time();
        $post['modified'] = time();
        $cpost = array();
        foreach ($post as $k => $v) {
            $cpost[':'.$k] = is_array($v) ? serialize($v) : $v;
        }
        $sql = "INSERT INTO ".$this->_table." (". implode(',',array_keys($post)).") VALUES (".implode(',',array_keys($cpost)).");";

        $add = $this->_dbh->prepare($sql);
        if ($add->execute($cpost)) {
            $id = $this->_dbh->lastInsertId();
            if ($meta) {
                foreach ($meta as $mk => $mv) {
                    $sql = 'insert into '.$this->_meta.' (meta_foreign_id,meta_key,meta_value) values (:fi,:mk,:mv)';
                    $add = $this->_dbh->prepare($sql);
                    $add->execute(
                        array(
                            ':fi' => $id,
                            ':mk' => $mk,
                            ':mv' => is_array($mv) ? serialize($mv) : $mv
                        )
                    );
                }
            }
            return $id;
        } else {
            return 0;
        }
    }
    public function set($post)
    {
        if (!isset($post['id'])) {
            return $this->add($post);
        }
        $id = $post['id'];
        if ($post['meta']) {
            $meta = $post['meta'];
            unset($post['meta']);
        }
        $post['modified'] = time();
        $cpost = array();
        foreach ($post as $k => $v) {
            $cpost[':'.$k] = is_array($v) ? serialize($v) : $v;
        }
        unset($cpost[':id']);
        $sql = ''; $parameters = array();
        $data = $executed = false;
        foreach ($post as $k => $v) {
            if ($k != 'id') {
                if (!$data) $sql = "UPDATE ".$this->_table." set ";
                $parameters[] = $k.' = :'.$k;
                $data = true;
            }
        }

        if ($data) {
            $sql .= implode(', ',$parameters).' where id = '.$id;
            $set = $this->_dbh->prepare($sql);
            $executed = $set->execute($cpost);
        }
        if (!empty($meta)) {
            $existing = $this->get($id);
//            $existing = $this->get(array('where' => array(
//                'id' => $id
//            )));
            foreach ($meta as $mk => $mv) {
                if (array_key_exists($mk, $existing[$id]['meta'])) {
                    $sql = 'update '.$this->_meta.' set meta_value = :mv where meta_foreign_id = '.$post['id'].' and meta_key = :mk;';
                    $set = $this->_dbh->prepare($sql);
                    $set->execute(
                        array(
                            ':mk' => $mk,
                            ':mv' => is_array($mv) ? serialize($mv) : $mv
                        )
                    );
                } else {
                    $sql = 'insert into '.$this->_meta.' (meta_foreign_id,meta_key,meta_value) values (:fi,:mk,:mv)';
                    $add = $this->_dbh->prepare($sql);
                    $add->execute(
                        array(
                            ':fi' => $post['id'],
                            ':mk' => $mk,
                            ':mv' => is_array($mv) ? serialize($mv) : $mv
                        )
                    );
                }
            }
        }
        return $executed ? $id : 0;
    }

    public function remove($params = array())
    {
        if ($params['id']) {
            $this->delete($params['id']);
            return $params;
        }
        $items = $this->get($params);

        $this->delete(array_keys($items));
        return array_keys($items);
    }

    public function delete($id)
    {
        if (is_array($id)) {
            if (isset($id['id'])) {
                $id = $id['id'];
                $sql = 'delete from '.$this->_meta.' where meta_foreign_id = '.$id;
                $del = $this->_dbh->prepare($sql);
                $del->execute();
                $sql = 'delete from '.$this->_table.' where id = '.$id;
                $del = $this->_dbh->prepare($sql);
                $del->execute();
            } else {
                $sql = 'delete from '.$this->_meta.' where meta_foreign_id in ('.implode(',', $id).')';
                $del = $this->_dbh->prepare($sql);
                $del->execute();
                $sql = 'delete from '.$this->_table.' where id in ('.implode(',', $id).')';
                $del = $this->_dbh->prepare($sql);
                $del->execute();
            }
        } else {
            $sql = 'delete from '.$this->_meta.' where meta_foreign_id = '.$id;
            $del = $this->_dbh->prepare($sql);
            $del->execute();
            $sql = 'delete from '.$this->_table.' where id = '.$id;
            $del = $this->_dbh->prepare($sql);
            $del->execute();
        }
    }
}