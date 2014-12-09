var namespace, FDO;
namespace = FDO = {};

FDO.tiers = {
    TIER_1 : 'Premium',
    TIER_2 : 'Platinum',
    TIER_3 : 'Professional'
};

FDO.exposeScope = true;
FDO.operatingMode = {};
FDO.operatingMode.legacy = false;
FDO.cacheKey = Math.floor(Math.random()*1000000);

FDO.duck = function(a) {
    if (typeof a === 'object' || typeof a === 'function') {
        if (typeof a.constructor === 'function') return a.constructor;
        if (typeof a.prototype === 'object' && typeof a.prototype.constructor === 'function') return Function;
    }
    if (typeof a === 'object') {
        if (a.length && typeof a.slice === 'function') return Array;
        return Object;
    }
    if (typeof a === 'function') return Function;
    if (typeof a === 'number') return Number;
    if (typeof a === 'string') return String;
    if (typeof a === 'boolean') return Boolean;
    if (typeof a === 'undefined') return undefined;
    if (typeof a === 'null') return null;
};

FDO.Post = function(url, data) {
    this.ingest(url, data);
};

FDO.Post.prototype = {
    form : null,
    ingest : function(url, data) {
        var form = $('<form/>').attr('action', url);
        form.attr('method', 'post');
        if (FDO.duck(data) == Object) {
            for (var i in data) {
                if (data.hasOwnProperty(i)) {
                    var input = $('<input/>');
                    input.attr('name', i);
                    input.val(data[i]);
                    input.attr('value', data[i]); // for visual reference
                    form.append(input);
                }
            }
        }
        form.css('display', 'none');
        $('body').append(form);
        this.form = form;
        return this;
    },
    submit : function() {
        this.form.submit();
    },
    debug : function() {
        console.log(this.form);
        window.f = this.form;
    }
};