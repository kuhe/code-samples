var NS = {};
/**
 * example:
 *
 * var userClickingRepeatedlyOnSlowApiButton = pool = new InputPooler
 *
 * eventBinding.click(pool(callback));
 *
 * When clicking rapidly, the callback only triggers during lulls in rapid input.
 * Originally this was used when I needed a way to reduce server load for a user clicking a button
 * repeatedly just to reach a certain number (e.g. online live bidding).
 */
var InputPooler = NS.InputPooler = (function() {
    var InputPooler = function() {
        this.init();
    };
    InputPooler.prototype = {
        identifier : 'InputPooler',
        constructor : InputPooler,
        latency : {
            current : 0,
            maximumWatchRange : 550,
            minimumReleaseRange : 200
        },
        commands : {},
        inputPeriods : [new Date().getTime(), new Date().getTime(), new Date().getTime()],
        init : function() {
            this.latency.current = this.latency.minimumReleaseRange;
            this.releaseWith = [];
        },
        releaseWith : [],
        chainOnExit : null,
        release : function() {
            if (typeof this.releaseWith == 'undefined') this.releaseWith = [];
            if (typeof this.releaseWith[0] == 'function') {
                if (typeof this.chainOnExit == 'function') {
                    this.releaseWith.shift()(this.chainOnExit);
                    this.chainOnExit = null;
                } else {
                    this.releaseWith.shift()();
                }
            } else {
                this.releaseWith.shift();
            }
        },
        /**
         * @param type
         * @param releaseFunction
         * @param onReleaseOnly
         * Pools callbacks into a queue which only fires the last one after a timeout
         * If onReleaseOnly is specified, then the callback will only fire upon release of the pool
         */
        pool : function(releaseFunction, onReleaseOnly) {
            var giraffe = this;

            if (!onReleaseOnly) {
                giraffe.inputPeriods.unshift(new Date().getTime());
                giraffe.inputPeriods = giraffe.inputPeriods.slice(0, 3);

                giraffe.latency.current += (giraffe.latency.maximumWatchRange/4);

                giraffe.latency.current = Math.min(giraffe.latency.maximumWatchRange,
                    Math.max(giraffe.latency.current, giraffe.latency.minimumReleaseRange));

                if (giraffe.inputPeriods[0] - giraffe.inputPeriods[1] > giraffe.latency.maximumWatchRange) {
                    giraffe.latency.current = giraffe.latency.minimumReleaseRange;
                }

                if (this.releaseWith.length) {
                    this.releaseWith.unshift(null);
                    this.releaseWith.pop();
                }
                this.releaseWith.push(releaseFunction);

                setTimeout(function(){giraffe.release()}, giraffe.latency.current);
            }
            if (onReleaseOnly) {
                giraffe.chainOnExit = releaseFunction;
                if (giraffe.releaseWith.length == 0) {
                    this.chainOnExit();
                }
            }
        },
        test : function() {

        }
    };
    return InputPooler;
})();

module.exports = InputPooler;