FDO.Registration = function(data) {
    this.init(data)
};

FDO.Registration.prototype = angular.extend(new FDO.DataObject, {
    identifier : 'Registration',
    constructor : FDO.Registration,
    columns : {
        register_id	:'id',
        username	:'username',
        password	:'password',
        firstname	:'firstName',
        lastname	:'lastName',
        company	    :'company',
        address1	:'address1',
        address2	:'address2',
        city	    :'city',
        state	    :'state',
        zip	        :'zip',
        country	    :'country',
        phone	    :'phone',
        email	    :'email',
        browser	    :'browser',
        maiden_name	:'maidenName',
        subplan	    :'plan',
        maxusers	:'maxUsers',
        amount	    :'amount',
        //cardname	:'cardName',
        //cardtype	:'cardType',
        //cardnum	    :'cardNumber',
        //cardexp	    :'cardExpiration',
        //cc_enc	    :'creditEncoded',
        //cc_md5	    :'creditMd5',
        pwd_q	    :'securityQuestion',
        pwd_a	    :'securityAnswer',
        registration_status_id:'status',
        date_created:'created',
        options	    :'options',
        username_orig:'originalUsername',
        referer	    :'referrer',
        referral	:'referral',
        referral_details:'referralDetails',
        //password_enc:'passwordEncoded',
        discount	:'discount'
    },
    initialize : function() {

    }
});