<?php

class Model_Monkey extends Model {
    public function getCuriousMonkeys() {
        return $this->get(array(
            'where' => array(
                'description' => 'curious'
            )
        ));
    }
}