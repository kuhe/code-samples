var InputPooler = require("./InputPooler.js");

/**
 * @type {InputPooler}
 * In the test method, greet is called 5 times, farewell is called once, then greet is called 5 times again asynchronously
 * The result is still: hello, bye
 */
var pool = new InputPooler;
var greet = function(bye) {console.log('hello'); if (typeof bye == 'function') bye()};
var farewell = function() {console.log('bye')};
var n = 0;
do {
    pool.pool(greet, false);
    n++;
} while (n < 5);
pool.pool(farewell, true);
setTimeout(function() {
    do {
        pool.pool(greet, false);
        n++;
    } while (n < 5);
}, 0);