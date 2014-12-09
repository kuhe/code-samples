var InputPooler = LA.InputPooler = (function() {
    var InputPooler = function() {
        if (InputPooler.instance) return InputPooler.instance;
        InputPooler.instance = this;
        this.releaseWith = [];
        return this.init();
    };
    InputPooler.prototype = {
        identifier : 'InputPooler',
        constructor : InputPooler,
        latency : { // milliseconds
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
        pool : function(type, releaseFunction) {
            var giraffe = this;

            if (type == 'Competing') {
                giraffe.chainOnExit = null;
                giraffe.inputPeriods.unshift(new Date().getTime());
                giraffe.inputPeriods = giraffe.inputPeriods.slice(0, 3);

                giraffe.latency.current += (giraffe.latency.maximumWatchRange/4);
                giraffe.latency.current = Math.min(giraffe.latency.maximumWatchRange, Math.max(giraffe.latency.current, giraffe.latency.minimumReleaseRange));
                if (giraffe.inputPeriods[0] - giraffe.inputPeriods[1] > giraffe.latency.maximumWatchRange) giraffe.latency.current = giraffe.latency.minimumReleaseRange;

                if (this.releaseWith.length) {
                    this.releaseWith.unshift(null);
                    this.releaseWith.pop();
                }
                this.releaseWith.push(releaseFunction);

                setTimeout(function(){giraffe.release()}, giraffe.latency.current);
            } else {
                giraffe.chainOnExit = releaseFunction;
                if (giraffe.releaseWith.length == 0) {
                    this.chainOnExit();
                }
            }
        }
    };
    return InputPooler;
})();
