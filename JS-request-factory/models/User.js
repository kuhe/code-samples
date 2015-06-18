NS.Item = function(data) {
    this.init(data)
};

NS.Item.prototype = framework.extend(NS.DataObject, {
    identifier : 'Item',
    constructor : NS.Item,
    columns : {
        id: 'id',
        name: 'name'
    },
    initialize : function() {

    }
});