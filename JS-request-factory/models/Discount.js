FDO.Discount = function(data) {
    this.init(data)
};

FDO.Discount.prototype = angular.extend(new FDO.DataObject, {
    identifier : 'Discount',
    constructor : FDO.Discount,
    columns : {
        id : 'id',
        created : 'created',
        description : 'description',
        feature : 'feature',
        isReoccuring : 'recurring',
        modified : 'modified',
        modified_by : 'modifiedBy',
        name : 'name',
        startDate : 'startDate',
        endDate : 'endDate',
        code : 'code',
        umbrellaCode : 'umbrella'
    },
    initialize : function() {
    }
});