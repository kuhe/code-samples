NS.DataObject = function() {
    this.init();
};

NS.DataObject.prototype = {
    identifier : 'DataObject',
    constructor : NS.DataObject,
    columns : {
        'db' : 'semantic'
    },
    init : function(data) {
        this.ingestFrom(data);
        return this.initialize()
    },
    initialize : function() {

    },
    ingestFrom : function(data) {
        if (typeof data == 'object') {
            for (var key in this.columns) {
                if (this.columns.hasOwnProperty(key)) {
                    this[this.columns[key]] = data[key]
                }
            }
        }
        return this;
    },
    toData : function() {
        var data = {};
        for (var key in this.columns) {
            if (this.columns.hasOwnProperty(key)) {
                data[key] = this[this.columns[key]];
            }
        }
        return data;
    }
};