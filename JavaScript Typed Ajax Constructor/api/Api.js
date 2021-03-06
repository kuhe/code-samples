var frameworkIterator = angular; // any generic iterator is fine too

/**
 * Manufactures CRUD requests for controller urls defined in a signature configuration file
 */
NS.Api = function(newInstance, definitions) {
    if (NS.Api.prototype.instance && !newInstance) return NS.Api.prototype.instance;
    if (!definitions) definitions = NS.apiDefinitions;
    this.help = definitions;
    NS.Api.prototype.instance = this;
    return this.init();
};

(function() {
    var Caster = {
        /**
         * Given raw object data and a constructor of the form Type or [Type], the
         * raw data will be cast to (via ingestion) the given type or a collection of that type.
         * For example constructor [User] will turn the input @param data into an array of User objects.
         * @param data {Object}
         * @param constructor {Function|Array<Function>}
         * @param complexConstructor {boolean} this indicates the cast will be an object with disparate types in each field
         * @returns {*}
         */
        ingest : function(data, constructor, complexConstructor) {
            if (!data) return data;
            if (typeof data == 'object' && data.length == 1 && !data[0]) return data[0];
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

            if (constructor.prototype && constructor.prototype.constructor == constructor) {
                if (typeof output == 'object' && typeof output.length == 'number') {
                    output = {};
                    frameworkIterator.forEach(data, function(item, key) {
                        var instance = new constructor(item);
                        output[instance.id] = instance;
                    });
                } else if (typeof output == 'object') {
                    return returnArray ? [new constructor(data)] : new constructor(data);
                }
            }
            return output;
        }
    };
    /**
     * Add a property under any CRUD operation that is an object with 'apiRoute', 'input' [optional], and 'output'. Input/output can be constructors.
     * The api will instantiate with such a method.
     */
    NS.Api.prototype = {
        /**
         * injected ajax implementation e.g. $.ajax or $http.post
         */
        ajax : null,
        last : {},
        instance: 1 instanceof NS.Api,
        REQUEST_ROOT : '/',
        help : null,
        /**
         * provide unified callback handling for simultaneous asynchronous requests via a simple counter.
         */
        init : function() {
            var giraffe = this;
            frameworkIterator.forEach(['create', 'read', 'update', 'delete'], function(action) {
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
            this.remove = this['delete'];
        },
        /**
         * baseline request that all generated methods are based on
         * @param address {string}
         * @param payload {object}
         * @param callback {Function}
         * @param resultSetType {Function|Array<Function>}
         * @param complexConstructor {boolean}
         */
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
        /**
         * Writes the api methods into the Api class from the signatures configuration
         */
        whoGetsTheGetters : function() {
            var definitions = this.help;
            for (var operation in definitions) { if (definitions.hasOwnProperty(operation)) {
                for (var call in definitions[operation]) { if (definitions[operation].hasOwnProperty(call)) {
                    if (['name'].indexOf(call) === -1 && definitions[operation][call].apiRoute) {
                        var signature = definitions[operation][call];
                        this[operation][call] = (function(signature, operation, call) {
                            var inputs = signature.input;
                            var fn = function() {
                                var i = 0,
                                    payload = {};
                                var args = arguments;
                                if (typeof args[0] != 'object') {
                                    if (typeof inputs == 'object') {
                                        frameworkIterator.forEach(inputs, function(item, key) {
                                            var input = args[i];
                                            if (!input) return true;
                                            if (typeof input.toData == 'function') input = input.toData();
                                            payload[key] = input;
                                            if (payload[key].constructor !== inputs[key]) {
                                                console.log(operation, call, key, 'got', payload[key], 'expected', inputs[key]);
                                            }
                                            i++;
                                        });
                                    }
                                } else {
                                    payload = arguments[0];
                                    frameworkIterator.forEach(payload, function(item, key) {
                                        if (typeof inputs == 'object') {
                                            if (payload[key].constructor !== inputs[key]) {
                                                console.log(operation, call, key, 'got', payload[key], 'expected', inputs[key]);
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
                            var inputCount = 0;
                            frameworkIterator.forEach(fn.help.input, function(item, key) {
                                if ([Function, Object, Array].indexOf(NS.duck(item)) > -1) {
                                    if (NS.duck(item.prototype) == Object && NS.duck(item.prototype.identifier) === String) {
                                        fn.help.inputTypes[key] = item.prototype.identifier;
                                    } else {
                                        fn.help.inputTypes[key] = 'mixed'
                                    }
                                }
                                inputCount++;
                            });
                            if (!inputCount) {
                                delete fn.help.inputTypes;
                            }
                            if ([Function, Object, Array].indexOf(NS.duck(fn.help.output)) > -1) {
                                if (NS.duck(fn.help.output.prototype) == Object && NS.duck(fn.help.output.prototype.identifier) === String) {
                                    fn.help.outputType = fn.help.output.prototype.identifier;
                                } else if (NS.duck(fn.help.output) === Array) {
                                    // todo check type better
                                    fn.help.outputType = 'Array<'+fn.help.output[0].prototype.identifier+'>'
                                } else {
                                    fn.help.outputType = 'mixed'
                                }
                            }
                            return fn;
                        })(signature, operation, call);
                    }}
                }}
            }
        },
        create : {},
        read : {},
        update : {},
        'delete' : {},

        'get' : {} // alias read
    };
})();