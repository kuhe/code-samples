<?php

namespace ApplicationTest\Model;

use ApplicationCommon\Db\DataResultSet;
use ApplicationCommon\Db\TableGateway\ReadOnlyReadyTableGateway;
use ApplicationCommon\Model\ActiveRecord;
use ApplicationCommon\Db\DataMapper;
use Exception;
use PHPUnit_Framework_TestCase as TestCase;
use Bootstrap;
use Zend\Db\Adapter\Exception\RuntimeException;


class Widget extends ActiveRecord {
    public $id;
    public $name;
    protected $adapterServiceName = 'generic_adapter';
    protected $tableName = '_test';
}
class Sprocket extends ActiveRecord {
    public $id;
    public $name;
    protected $adapterServiceName = 'generic_adapter';
    protected $tableName = '_test';
}


class ActiveRecordTest extends TestCase {

    public $locator;
    public function setup() {
        $this->locator = \Bootstrap::$sm;
        ActiveRecord::setServiceLocator($this->locator);
    }
    public function tearDown() {

    }

    /**
     * @expectedException Exception
     */
    public function testInstantiationWithoutLocator() {
        ActiveRecord::setServiceLocator(null);
        $record = new Widget;
    }

    public function testInstantiation() {
        $record = new Widget();
        $this->assertTrue($record instanceof ActiveRecord);
    }

    public function testSingleton() {
        $this->assertTrue(new Widget === Widget::instance());
        $this->assertTrue(Widget::instance() === Widget::instance());
        $this->assertFalse(Sprocket::instance() === Widget::instance());
        $this->assertTrue(Sprocket::instance() === Sprocket::instance());
    }

    public function testMapper() {
        $record = new Widget;
        $mapper = $record->getMapper();
        $gateway = $mapper->getTableGateway();

        $this->assertTrue($mapper instanceof DataMapper);
        $this->assertTrue($mapper::gateway($record, $record->getServiceLocator()) instanceof ReadOnlyReadyTableGateway);
        $this->assertEquals($mapper::gateway($record, $record->getServiceLocator()), $gateway);
        $this->assertEquals($mapper, DataMapper::instance($gateway, $record));
    }

    public function testRead() {
        $records = Sprocket::get();
        $this->assertTrue($records instanceof DataResultSet);
        $rowCount = $records;
        $this->assertTrue(is_integer(count($rowCount)));
    }

    public function testWrite($rowCount) {
        $record = new Sprocket();
        $record->name = 'test';
        $id = $record->save();
        $sprocket = Sprocket::getOne($id);
        $deletions = $sprocket->delete();

        $this->assertEquals($deletions, 1);
        $this->assertTrue(is_integer((int)$id), "$id should be integer");
        $this->assertTrue($sprocket instanceof Sprocket, "get($id) should retrieve instance");
        $this->assertFalse(Sprocket::getOne($id + 1) instanceof Sprocket);
        $this->assertEquals($sprocket->name, 'test');

        $sprocket2 = new Sprocket();
        $this->assertFalse($sprocket2->update());

        $sprockets = Sprocket::get();
        $this->assertEquals(count($sprockets), $rowCount);
        $this->assertFalse(Sprocket::getOne($id) instanceof Sprocket, 'should have been deleted');
    }

    public function testCast() {
        $widget = new Widget();
        $widget->name = 'test';
        $arrayForm = $widget->toArray();

        $this->assertEquals($arrayForm['name'], 'test');
        $this->assertTrue((new Widget())->ingest($arrayForm) instanceof Widget);
        $this->assertFalse((new Widget())->ingest($arrayForm) instanceof Sprocket);

        $this->assertEquals((new Widget())->ingest($arrayForm)->name, 'test');
        $this->assertEquals((new Widget())->ingest($widget)->name, 'test');
        $this->assertContains('name', $widget->getFields());
        $this->assertContains('id', $widget->getFields());
    }

    /**
     * @expectedException RuntimeException
     */
    public function testIteration() {
        $widget = new Widget();
        $this->assertTrue(is_array($widget->getKey()));
        $this->assertTrue(count($widget->getKey()) == 1);
        $widget->name = 'iteration';
        $widget->add();
        $widget->add();
        $iterations = Widget::get(array('name' => 'iteration'));
        $widget->delete(array('name' => 'iteration'));
        $n = 0;

        foreach ($iterations as $iteration) {
            $n++;
            $this->assertEquals('iteration', $iteration->name);
            $this->assertTrue($iteration instanceof Widget);
            $this->assertFalse($iteration instanceof Sprocket);
        }
        $this->assertEquals(2, $n);
        foreach ($iterations as $iteration) {
            // unfortunately, should throw exception
        }
    }

    public function testArrayIteration() {
        $widget = new Widget();
        $widget->name = 'iteration';
        $widget->add();
        $widget->add();
        $iterations = Widget::get(array('name' => 'iteration'))->toArray();
        $widget->delete(array('name' => 'iteration'));
        $n = 0;
        foreach ($iterations as $iteration) {
            $n++;
            $this->assertEquals('iteration', $iteration['name']);
        }
        $this->assertEquals(2, $n);
        $n = 0;
        foreach ($iterations as $iteration) {
            $n++;
            $this->assertEquals('iteration', $iteration['name']);
        }
        $this->assertEquals(2, $n);
    }

}