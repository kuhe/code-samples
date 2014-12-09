var Item = Namespace.Item = (function(jQuery) {
    var $ = jQuery;
    var Item = function(data) {
        DataObject.prototype.initialize.call(this, data);
    };
    Item.prototype = $.extend(new DataObject, {
        constructor : Item,
        identifier : 'Item',
        dataProperties : {
            // canonical
            'id': 'id',
            '_id': '_id',
            "name": "name",
            "description": "description"
        },
        init : function(data) {
            if (data == 'dummy') {
                
            } else {
                
            }
        }
    });
    return Item;
})($);