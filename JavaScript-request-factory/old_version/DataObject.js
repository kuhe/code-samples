var DataObject = Namespace.DataObject = (function(jQuery) {
    var $ = jQuery;
    var DataObject = function(data) {
    };
    DataObject.prototype = {
        constructor : DataObject,
        identifier : 'DataObject',
        heretical : {},
        dataProperties : {
            databaseFieldName : 'semanticClientSideFieldName'
        },
        initialize: function(data) {
            this.heretical = {};
            var heretical = false;
            if (data != 'dummy') {
                for (var key in data) {
                    if (this.hasDataProperty(key)) {
                        this[this.hasDataProperty(key)] = data[key];
                    } else {
                        heretical = true;
                        this.heretical[key] = data[key];
                        this[key] = data[key]
                    }
                }
                if (heretical) Namespace.heretics.push(this);
            }
            if (!this.id && this._id) {
                if (typeof this._id == 'object') {
                    this.id = this._id.$oid;
                }
                this.id = this._id;
            }
            if (this.id && Namespace.objectCache) {
                typeof Namespace.objectCache[this.identifier] == 'undefined' && (Namespace.objectCache[this.identifier] = {});
                if (typeof Namespace.objectCache[this.identifier][this.id] != 'undefined') {
                    Namespace.objectCache[this.identifier][this.id] = this;
                } else {
                    Namespace.objectCache[this.identifier][this.id] = $.extend(Namespace.objectCache[this.identifier][this.id], this);
                }
            }
            this.init(data);
        },
        init : function(data) {

        },
        hasDataProperty : function(field) {
            return this.dataProperties[field]
        },
        toData : function() {
            var data = {};
            for (var i in this.dataProperties) if (this.hasOwnProperty(this.dataProperties[i])) data[i] = this[this.dataProperties[i]];
            return data;
        },
        getDummy : function() {
//            var data = {};
//            var constructor,
//                name;
//            for (var key in this.dataProperties) {
//                name = this.dataProperties[key];
//                constructor = Namespace[name[0].toUpperCase() + name.slice(1)]
//                if (typeof constructor == 'function' && constructor.prototype.identifier) {
//                    data[key] = new constructor('dummy').toData();
//                    console.log(constructor);
//                } else {
//                    data[key] = '1';
//                }
//            }
            return new this.constructor('dummy');
        }
    };
    return DataObject;
})($);
