var namespace, NS;
namespace = NS = {};

NS.duck = function(a) {
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

// factory-ize it

angular.module('nsApi', [])
    .factory('nsApi', ['$http', function($http) {
        this.$get = function() {};
        NS.Api.prototype.ajax = $http;
        return new NS.Api;
    }]);