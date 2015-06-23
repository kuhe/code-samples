var Api = Namespace.Api = (function(jQuery) {

    var withoutJSON = [];
    var excludeRoutePrefixes = ['read.stats'];
    var definitions = {
        create : {
            name : 'create',
            apiRoutePrefix : 'c_',
            user : {
                help : {
                    apiRouteSuffix : 'usr',
                    input : {
                        user : User
                    },
                    output : true // boolean/bit
                }
            },
            item : {
                help : {
                    apiRouteSuffix : 'item',
                    input : {
                        item : Item
                    },
                    output : true // boolean/bit
                }
            }
        },
        read : {
            name : 'read',
            apiRoutePrefix : 'r_',
            user : {
                help : {
                    apiRouteSuffix : 'usr',
                    input : {
                        email : ''
                    },
                    output : User
                }
            },
            item : {
                help : {
                    apiRouteSuffix : 'item',
                    input : {
                        itemid : '1'
                    },
                    output : Item
                }
            },
            stats : {
                help : {
                    apiRouteSuffix : 'stats',
                    input : {},
                    output : {}
                }
            }
        },
        update : {
            name : 'update',
            apiRoutePrefix : 'u_',
            user : {
                help : {
                    apiRouteSuffix : 'usr',
                    input : {
                        user : User
                    },
                    output : true //bool
                }
            },
            item : {
                help : {
                    apiRouteSuffix : 'item',
                    input : {
                        item : Item
                    },
                    output : true //bool
                }
            }
        },
        'delete' : {
            name : 'delete',
            apiRoutePrefix : 'd_',
            user : {
                help : {
                    apiRouteSuffix : 'usr',
                    input : {
                        email : 'string'
                    },
                    output : true //bool
                }
            },
            item : {
                help : {
                    apiRouteSuffix : 'item',
                    input : {
                        itemid : '1'
                    },
                    output : true //bool
                }
            }
        }
    };

    var Caster = {
        ingest : function(data, constructor) {
            if (typeof data == 'undefined') return;
            if (!constructor) return data;
            var output = data;
            if (constructor.prototype && constructor.prototype.identifier && constructor.prototype.constructor == constructor) {
                if (typeof data.length == 'number') {
                    output = [];
                    $.each(data, function(key, item) {
                        output[key] = new constructor(item);
                    });
                } else if (typeof data == 'object') {
                    return [new constructor(data)];
                }
            }
            return output;
        }
    };

    var $ = jQuery;
    var tools = {
        extend : $.extend,
        ajax : $.ajax
    };

    var Cache = function(){
        this.defaultInvalidationAge = 360; // in seconds
        this.enabled = true;
    };
    Cache.prototype = new LocalStorage(false);

    var Api = function(newInstance) {
        if (Api.prototype.instance && !newInstance) return Api.prototype.instance;
        Api.prototype.instance = this;
        this.cache = new Cache;
        return this.init();
    };
    Api.prototype = {
        constructor : Api,
        identifier : 'Api',
        REQUEST_URL_ROOT : '//'+document.domain+'/api/',
        DEFAULT_VERSION : 1,

        instance : null,
        cache : Cache,

        init : function() {
            var giraffe = this;
            $.each(['create', 'read', 'update', 'delete'], function(key, action) {
                var callbackTriggerCount = undefined,
                    callbackCount = 0,
                    results = [];
                giraffe[action] = function(calls) {
                    typeof callbackTriggerCount == 'undefined' && (callbackTriggerCount = calls.length - 1);
                    $.each(calls, function(key, item) {
                        if (typeof item == 'object' && item.length) {
                            var callback = function(result) {
                                results[key] = result;
                                if (++callbackCount == callbackTriggerCount) {
                                    calls[calls.length - 1](results);
                                    callbackTriggerCount = undefined;
                                    callbackCount = 0;
                                    results = [];
                                }
                            };
                            if (!item[1]) {
                                giraffe[action][item[0]](callback);
                            } else {
                                giraffe[action][item[0]](item[1], callback);
                            }
                        }
                    });
                };
                giraffe[action].help = definitions[action];
                for (var i in definitions[action]) {
                    giraffe[action][i] = definitions[action][i];
                }
            });
            this.whoGetsTheGetters();
        },
        request : {
            simple : function(url, data, callback) {
                if (!data) data = {};
                if (!data.v) data.v = Api.prototype.DEFAULT_VERSION;
                data.withoutJSON = !!(withoutJSON.indexOf(url) + 1);
                var giraffe = this;
                var jqXHR = tools.ajax({
                    type : 'POST',
                    url: Api.prototype.REQUEST_URL_ROOT + url,
                    dataType: 'text',
                    data: {
                        _xsrf : $('.xsrf.hide input').val(),
                        data : JSON.stringify(data)
                    }
                });
                jqXHR.always(function(result, textStatus, jqXHR) {
                    var parseResult = giraffe.parse('simple', result, '');
                    giraffe.last = {
                        simple: true,
                        succeeded : true,
                        argument : data,
                        result : result,
                        parseResult : parseResult,
                        jqXHR : jqXHR
                    };
                    if (typeof callback == 'function') {
                        giraffe.last.callbackResult = callback(parseResult);
                    } else {
                        giraffe.last.callbackResult = 'no callback';
                    }
                });
            },
            standard : function(operation, prescription, callerName, argument, callback) {
                var baseArgument = $.extend({}, argument);
                delete baseArgument.fresh;
                delete baseArgument.ageLimit;
                var cacheKey = operation.help.name+'.'+callerName+'('+JSON.stringify(baseArgument)+')';
                this.requestStartTime = new Date().getTime();
                if (operation.help.name == 'read' && (new Api).cache.enabled
                    && !argument.fresh && !prescription.alwaysFresh && (new Api).cache.get(cacheKey)) {
                    var cacheData = (new Api).cache.get(cacheKey);
                    var ageLimit = prescription.ageLimit ? prescription.ageLimit : (new Api).cache.defaultInvalidationAge;
                    if (ageLimit && cacheData && new Date(cacheData.last).getTime() + ageLimit * 1000 < new Date().getTime()) {

                    } else {
                        cacheData.hits++;
                        cacheData.last = new Date();
                        if (typeof callback == 'function') {
                            setTimeout(function(){callback(cacheData.data)}, 1);
                        }
                        return
                    }
                }
                var route = Api.prototype.routeRequest(operation, prescription);
                var giraffe = this;
                var data = typeof argument == 'object' ? argument : {arg : argument};

                if (!data.hasOwnProperty('v')) data.v = Api.prototype.DEFAULT_VERSION;

                var jqXHR = tools.ajax({
                    type : 'POST',
                    url: route,
                    dataType: 'text',
                    data: {
                        _xsrf : $('.xsrf.hide input').val(),
                        data : JSON.stringify(data)
                    }
                });
                jqXHR.fail(function(jqXHR, textStatus, errorThrown) {
                    giraffe.last = {
                        succeeded : false,
                        argument : argument,
                        route : route,
                        callbackResult : null,
                        jqXHR : jqXHR,
                        textStatus : textStatus,
                        errorThrown : errorThrown
                    };
                    if (typeof callback == 'function') {
                        callback(undefined);
                    }
                });
                jqXHR.done(function(result, textStatus, jqXHR) {
                    var parseResult = giraffe.parse(operation, result, callerName);
                    giraffe.last = {
                        succeeded : true,
                        argument : argument,
                        route : route,
                        result : parseResult,
                        rawResult : result,
                        textStatus : textStatus,
                        jqXHR : jqXHR
                    };
                    if (typeof callback == 'function') {
                        giraffe.last.callbackResult = callback(parseResult);
                    } else {
                        giraffe.last.callbackResult = 'no callback';
                    }

                    var performance = 0;
                    if ((new Api).cache.enabled) {
                        if (!(new Api).cache.get(cacheKey)) {
                            performance = new Date().getTime() - giraffe.requestStartTime;
                            (new Api).cache.set(cacheKey, {
                                data : parseResult,
                                marginalRequestTime : performance,
                                hits : 1,
                                refreshes : 1,
                                last : new Date()
                            });
                            console.log('incremental response time: ' + cacheKey.split('(')[0], performance, 'ms');
                            giraffe.requestStartTime = new Date().getTime();
                        } else {
                            var cacheData = (new Api).cache.get(cacheKey);
                            cacheData.data = parseResult;
                            cacheData.hits++;
                            cacheData.refreshes++;
                            cacheData.last = new Date();
                            (new Api).cache.set(cacheKey, cacheData);
                            performance = new Date().getTime() - giraffe.requestStartTime;
                            console.log('incremental response time: ' + cacheKey.split('(')[0], performance, 'ms');
                        }
                    }
                });
            },
            last : {
                succeeded : null,
                argument : null,
                route : null,
                callbackResult : null,
                result : null
            },
            parse : function(operation, input, argument) {
                var output = {error : {}};
                try {
                    output = $.parseJSON(input);
                } catch (e) {
                    (!operation || !operation.help || operation.help.name) && (operation = {}, operation.help = {}, operation.help.name = '');
                    console.log('api json parse error', {result: input, apiCall: operation.help.name + ' ' + argument});
                    return null;
                }
                if (output.hasOwnProperty('resp')) {
                    if (operation == 'simple') {
                        constructor = null
                    } else {
                        constructor = (new Api)[operation.help.name][argument].help.output
                    }
                    if (output.resp.hasOwnProperty('data')) {
                        return Caster.ingest(output.resp.data, constructor);
                    }
                    return Caster.ingest(output.resp, constructor);
                } else {
                    console.log('response malformed', output);
                    return output;
                }
            }
        },
        routeRequest : function(operation, prescription) {
            var prefix = operation.apiRoutePrefix;
            if (excludeRoutePrefixes.indexOf(operation.help.name + '.' + prescription.apiRouteSuffix) > -1) {
                prefix = '';
            }
            return this.REQUEST_URL_ROOT + prefix + prescription.apiRouteSuffix;
        },
        whoGetsTheGetters : function() {
            var giraffe = this;
            $.each([giraffe.create, giraffe.read, giraffe.update, giraffe['delete']], function(index, operation) {
                $.each(operation, function(name, functionalDefinition) {
                    if (!functionalDefinition.hasOwnProperty('help')) return true;
                    var request;
                    var prescription = functionalDefinition.help;
                    if (typeof prescription == 'object' && prescription.input) {
                        request = function() {
                            return function() {
                                var callback = (arguments.length && typeof arguments[arguments.length-1] == 'function' ? arguments[arguments.length-1] : null);
                                if (typeof arguments[0] != 'object') {
                                    var input = {};
                                    var index = 0;
                                    var scopeArguments = arguments;
                                    $.each(prescription.input, function(key, type) {
                                        if (!!prescription.input[key].prototype && prescription.input[key].prototype.hasOwnProperty('identifier')) {
                                            if (prescription.input[key].prototype.hasOwnProperty('identifier')
                                                && typeof scopeArguments[index]['toData'] == 'function')
                                            input[key] = scopeArguments[index++].toData();
                                        } else {
                                            input[key] = scopeArguments[index++];
                                        }
                                    });
                                    giraffe.request.standard(operation, prescription, name, input, callback);
                                } else {
                                    var data = arguments[0].identifier ? arguments[0].toData() : arguments[0];
                                    giraffe.request.standard(operation, prescription, name, data, callback);
                                }
                            }
                        };
                    } else {
                        request = function() {
                            return function(callback) {
                                giraffe.request.standard(operation, prescription, name, {}, callback);
                            }
                        };
                    }
                    var method = new request();
                    method.help = functionalDefinition.help;
                    operation[name] = method;
                });
            });
            this.get = this.read;
            this.set = this.update;
            this.save = this.create;
        },

        create : function() {}, // constructor assignment
        read : {}, // constructor assignment
        update : {}, // constructor assignment
        'delete' : {}, // constructor assignment

        'get' : null, // alias
        'set' : null, // alias
        save : null, // alias

        test : {
            passes : [],
            failures : [],
            last : null,
            suite : function() {
                this.passes = [];
                this.failures = [];
                var TestResult = function() {};
                TestResult.prototype = this.last = {
                    main : (this.main(), 'pending'),
                    singleton : this.singleton()
                };
                return new TestResult;
            },
            singleton : function() {
                return new Api == new Api && !!this.passes.push('singleton') || !!this.failures.push('singleton');
            },
            main : function() {
                var log = function() {
                    console.log.apply(console, arguments);
                };
                var zebra = this;
                var api = new Api;
                var testIndex = 0,
                    callbackIndex = 0,
                    memory = {};
                for (var operation in {create: 1, read: 1, update: 1, 'delete': 1}) {
                    for (var key in api[operation].help) {
                        if ({ apiRoutePrefix : 1, name : 1 }[key]) continue;
                        var prescription = api[operation][key].help;
                        var inputs = prescription.input;
                        var inputArguments = {};
                        for (var input in inputs) {
                            if (typeof inputs[input] == 'function' && inputs[input].prototype.hasOwnProperty('identifier')) {
                                inputArguments[input] = (typeof inputs[input].prototype.getDummy == 'function' ?
                                    (new inputs[input]).getDummy() : new inputs[input]).toData();
                            } else {
                                inputArguments[input] = prescription.input[input];
                            }
                        }
                        if (operation == 'read') inputs.fresh = true;
                        var description = $.extend({}, prescription);
                        memory[testIndex++] = [operation, key];

                        api[operation][key](inputArguments, function(result) {
                            var cast = typeof description.output == 'function' && description.output.prototype.hasOwnProperty('identifier');
                            (cast ? result instanceof description.output : typeof result == typeof description.output)
                                && zebra.passes.push(memory[callbackIndex++].join(' ')) || zebra.failures.push(memory[callbackIndex++].join(' '));
                            if (callbackIndex == testIndex)
                                log(
                                    'Callbacks complete.',
                                    zebra.passes.length + ' passing:',
                                    zebra.passes,
                                    zebra.failures.length + ' failing:',
                                    zebra.failures
                                );
                        });
                    }
                }
            }
        }
        
    };

    return Api;
})($);