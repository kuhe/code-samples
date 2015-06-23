NS.Item = function(data) {
    this.init(data)
};

NS.Item.prototype = framework.extend(NS.DataObject, {
    identifier : 'Item',
    constructor : NS.Item,
    columns : {
        country_code : 'countryCode',
        state_code : 'code',
        state_name : 'name',
        state_id : 'id'
    },
    initialize : function() {

    }
});