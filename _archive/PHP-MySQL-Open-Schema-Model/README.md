Code Sample (PHP ZF1)

Model
=====

A toy implementation of the ORM used at HealthGuru in ~2012 written by Faisal Raja, Lei Xu, Almond Mendoza, Khaled Alquaddoomi (I think).

EAV PHP MySQL query class I use for small projects so I can have control over the query syntax;
can be modified not to use Zend Framework registry.

sample usage:

    $monkeyModel = Tower::model('monkey', false); // params table name & object mode, returns query class
    $monkeyModel = Tower::model('monkey'); //default is object mode

    $allMonkeys = $monkeyModel->get(); // returns array indexed by primary key

    $curiousMonkeys = $monkeyModel->get($curious = array(
        'where' => array(
            'description' => 'curious'
        )
    )); // takes array with query parameters

    // or use custom methods written into the class
    $curiousMonkeys = $monkeyModel->getCuriousMonkeys();

    // spare one monkey
    $lastMonkey = end($curiousMonkeys);

    //either use array mode:
    $lastMonkey['description'] = 'no longer curious';
    $lastMonkey['meta']['is_eav'] = true; // will save to corresponding meta table
    $lastMonkey['meta']['arbitrary_key'] = array('arbitrary values', 2, 3, 'banana');
    $monkeyModel->save($lastMonkey); // upsert functionality

    //or object mode, depending on how the model was initialized:
    $lastMonkey->suppressCuriosity(); // custom methods added arbitrarily to the class

    // into the wild
    $freeCuriousMonkeys = $monkeyModel->remove($curious);

todo :

    result caching
    query optimization - combining looped calls
    (?) new php versions of PDO don't require manual serialization?
    I should probably test this, eh.
