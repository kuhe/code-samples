<?php

namespace AR\Model;

/**
 * Class ActiveRecord
 * @package AR\Model
 *
 * Calling it what it is.
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