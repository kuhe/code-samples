FDO.Country = function(data) {
    this.init(data)
};

FDO.Country.prototype = angular.extend(new FDO.DataObject, {
    identifier : 'Country',
    constructor : FDO.Country,
    columns : {
        country_code : 'code',
        country_name : 'name',
        country_id : 'id'
    },
    initialize : function() {

    }
});