FDO.Plan = function(data) {
    this.init(data)
};

FDO.Plan.prototype = angular.extend(new FDO.DataObject, {
    identifier : 'Plan',
    constructor : FDO.Plan,
    columns : {
        subplan_id : 'id',
        amount : 'amount',
        maxusers : 'maxUsers',
        months : 'months',
        charge : 'isCredit',
        description : 'description',
        book : 'includesBook',
        active : 'status',
        'package' : 'package',
        plan_name : 'name'
    },
    initialize : function() {
    },
    getTier : function() {
        return this.id.slice(0, 1);
    },
    getPeriod : function() {
        var period = this.months == '1' ? 'monthly' : 'annually';
        if (this.months != 12 && this.months != 1) {
            period = 'every ' + this.months + ' months';
        }
        return period;
    },
    getIdentifier : function() {
        return [this.getTier(), this.maxUsers, this.isCredit, this.months].join('_');
    },
    usesCredit : function() {
        return !!parseInt(this.isCredit);
    },
    keyPlans : function(plans) {
        for (var id in plans) {
            if (plans.hasOwnProperty(id) && plans[id] instanceof FDO.Plan) {
                var plan = plans[id];
                var key = [plan.id[0], parseInt(plan.maxUsers), parseInt(plan.isCredit), parseInt(plan.months)].join('_');
                plans[key] = plans[id];
            }
        }
        return plans;
    }
});