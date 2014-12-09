/**
 * Manufactures CRUD requests for controller urls defined in the "definitions" file
 */
NS.Api = function(newInstance) {
    if (NS.Api.prototype.instance && !newInstance) return NS.Api.prototype.instance;
    NS.Api.prototype.instance = this;
    return this.init();
};

(function() {
    var Caster = {
        ingest : function(data, constructor, complexConstructor) {
            var output = data;
            if (complexConstructor) {
                for (var i in output) {
                    if (output.hasOwnProperty(i)) {
                        output[i] = Caster.ingest(output[i], constructor[i], false);
                    }
                }
                return output;
            }
            if (typeof output == 'undefined') return;
            if (!constructor) return output;

            var returnArray = NS.duck(constructor) == Array;
            if (returnArray) constructor = constructor[0];

            if (!returnArray && NS.duck(output) == Array && output.length == 1) {
                output = output[0];
            }

            if (constructor.prototype && constructor.prototype.identifier && constructor.prototype.constructor == constructor) {
                if (typeof data.length == 'number') {
                    output = {};
                    angular.forEach(data, function(item, key) {
                        var instance = new constructor(item);
                        output[instance.id] = instance;
                    });
                } else if (typeof data == 'object') {
                    return returnArray ? [new constructor(data)] : new constructor(data);
                }
            }
            return output;
        }
    };
    /**
     * Add a property under any CRUD operation that is an object with 'apiRoute', 'input' [optional], and 'output'. Input/output can be constructors.
     * The api will instantiate with such a method.
     *
     * e.g. under read, test : { apiRoute: 'base/test', input: {hello: 1}, output: NS.Discount }
     * will allow NS.Api to instantiate with asynchronous callable
     * (new NS.Api).read.test([int @hello], [callable @callback(data)])
     * Where data represents the request response cast to an array (0 or more elements) of the output type, here NS.Discount
     */
    var definitions = NS.apiDefinitions;
    NS.Api.prototype = {
        ajax : null,
        last : {},
        instance: null instanceof NS.Api,
        REQUEST_ROOT : '/',
        init : function() {
            var giraffe = this;
            angular.forEach(['create', 'read', 'update', 'delete'], function(action) {
                var data = {};
                var trigger;
                giraffe[action] = function(calls) {
                    var args = arguments;
                    trigger = args.length - 1;
                    var callback = function() {
                        if (trigger === 0) {
                            args[args.length - 1](data);
                        }
                    };
                    var storeResult = function(method, result) {
                        return function(result) {
                            var key = method;
                            var n = 1;
                            while (data[key]) {
                                key = method + n;
                                n++;
                            }
                            data[key] = result;
                            trigger--;
                            callback();
                        }
                    };
                    for (var i = 0; i < args.length; i++) {
                        if (typeof args[i] == 'string' && giraffe[action][args[i]]) {
                            var method = args[i];
                            var call = (function(method) {
                                giraffe[action][method](storeResult(method));
                            })(method);
                        } else if (args[i].length && typeof args[i] == 'object') {
                            method = args[i][0];
                            var inputs = args[i][1];
                            call = (function(method) {
                                giraffe[action][method](inputs, storeResult(method));
                            })(method);
                        }
                    }
                };
            });
            this.whoGetsTheGetters();
            this.get = this.read;
        },
        simpleRequest : function(address, payload, callback, resultSetType, complexConstructor) {
            if (typeof payload != 'object') {
                payload = {
                    data : payload
                }
            }
            var giraffe = this;
            if (!this.ajax) throw 'NS.Api ajax not set';
            var promise = this.ajax.post(this.REQUEST_ROOT + address, payload);
            promise.success(function(result, status, headers, config) {
                giraffe.last = {
                    result: result,
                    status: status,
                    headers: headers,
                    config: config
                };
                var data = Caster.ingest(result.data, resultSetType, complexConstructor);
                if (typeof callback == 'function') {
                    callback(data);
                }
            });
            promise.error(function(result) {
                giraffe.last = result;
            });
        },
        whoGetsTheGetters : function() {
            for (var operation in definitions) {
                if (definitions.hasOwnProperty(operation)) {
                    for (var call in definitions[operation]) {
                        if (definitions[operation].hasOwnProperty(call)) {
                            if (['name'].indexOf(call) === -1 && definitions[operation][call].apiRoute) {
                                var signature = definitions[operation][call];
                                this[operation][call] = (function(signature) {
                                    var inputs = signature.input;
                                    var fn = function() {
                                        var i = 0,
                                            payload = {};
                                        var args = arguments;
                                        if (typeof args[0] != 'object') {
                                            if (typeof inputs == 'object') {
                                                angular.forEach(inputs, function(item, key) {
                                                    var input = args[i];
                                                    if (typeof input.toData == 'function') input = input.toData();
                                                    payload[key] = input;
                                                    if (payload[key].constructor !== inputs[key]) {
                                                        console.log(payload[key], 'input type unexpected', inputs[key]);
                                                    }
                                                    i++;
                                                });
                                            }
                                        } else {
                                            payload = arguments[0];
                                            angular.forEach(payload, function(item, key) {
                                                if (typeof inputs == 'object') {
                                                    if (payload[key].constructor !== inputs[key]) {
                                                        console.log(payload[key], 'input type unexpected', inputs[key]);
                                                    }
                                                }
                                                if (typeof item.toData == 'function') payload[key] = item.toData();
                                            });
                                        }
                                        var callback = arguments[arguments.length - 1];
                                        (new NS.Api).simpleRequest(signature.apiRoute, payload, callback, signature.output, signature.complexOutput);
                                    };
                                    fn.help = signature;
                                    fn.help.inputTypes = {};
                                    angular.forEach(fn.help.input, function(item, key) {
                                        if (typeof item == 'function') {
                                            fn.help.inputTypes[key] = item.prototype.identifier;
                                        } else {
                                            fn.help.inputTypes[key] = typeof item;
                                        }
                                    });
                                    if (typeof fn.help.output == 'function') {
                                        fn.help.outputType = fn.help.output.prototype.identifier;
                                    }
                                    return fn;
                                })(signature);
                            }
                        }
                    }
                }
            }
        },
        create : {},
        read : {},
        update : {},
        'delete' : {},

        'get' : {} // alias read
    };
})();