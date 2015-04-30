<?php

namespace ApplicationCommon\Model;

/**
 * Class ActiveRecord
 * @package ApplicationCommon\Model
 *
 * But it violates SRP in SOLID!
 *
 */
abstract class ActiveRecord extends DataObject {
    /**
     * @var string required
     */
    protected $adapterServiceName;
    /**
     * @var string required
     */
    protected $tableName;
}