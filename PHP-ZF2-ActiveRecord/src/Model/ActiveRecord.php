<?php

namespace FCCommon\Model;

/**
 * Class ActiveRecord
 * @package FCCommon\Model
 *
 * Calling it what it is.
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