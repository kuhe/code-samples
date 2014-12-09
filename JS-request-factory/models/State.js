FDO.State = function(data) {
    this.init(data)
};

FDO.State.prototype = angular.extend(new FDO.DataObject, {
    identifier : 'State',
    constructor : FDO.State,
    columns : {
        country_code : 'countryCode',
        state_code : 'code',
        state_name : 'name',
        state_id : 'id'
    },
    initialize : function() {

    }
});