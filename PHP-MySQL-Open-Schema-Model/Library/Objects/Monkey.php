<?php

class Object_Monkey extends DataObject {
    public function isCurious() {
        return $this->isCurious || $this->description == 'curious';
    }
    public function suppressCuriosity() {
        $this->isCurious = false;
        $this->description = 'no longer curious';
        return $this->save();
    }
}