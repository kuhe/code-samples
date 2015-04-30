### ActiveRecord for ZF2

Shoehorning active record pattern on top of data mapper pattern, using ZF2's sql classes.
Likely a violation of many good principles, but it's so convenient to use! 

 
    class Widget extends ActiveRecord {}

Static reads:

    $widgets = Widget::get(Predicate|array|null); // summons the data mapper from behind-the-scenes cache, returns the result set as instances of itself
    $widget = Widget::getOne(Predicate|array|null);
    // e.g.
    $widget = Widget::getOne(['name' => 'Roberts']);

Instance writes:

    $widget->name = 'Sprocket';
    $widget->save(); // upsert
    $widget->delete();
    
Typing:
    
    $widget instanceof Widget === true; // yay
    
Convenience methods:

    $widgets instanceof DataResultSet === true; // true
    
    $widgets->toArray();
    $widget->toArray();