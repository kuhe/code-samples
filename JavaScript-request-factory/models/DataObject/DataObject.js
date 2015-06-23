/**
 * Provides a base class that maps between data and the front end model
 * @constructor
 */
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
    },
    toDate : function(dateString) {
        dateString = dateString + ' ';
        if (!dateString) return null;
        var n = -1,
            date = dateString;
        while (isNaN(date) && n > -20 && typeof dateString.slice == 'function') {
            date = new Date(dateString.slice(0,n));
            n--;
        }
        if (!(date instanceof Date)) return null;
        return date;
    }
};