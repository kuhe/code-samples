FDO.Member = function(data) {
    this.init(data)
};

FDO.Member.prototype = angular.extend(new FDO.DataObject, {
    identifier : 'Member',
    constructor : FDO.Member,
    columns : {
        'member_id': 'id',
        'username': 'username',
        //'password': 'password',
        'firstname': 'firstName',
        'lastname': 'lastName',
        'company': 'company',
        'contact': 'contact',
        'note': 'note',
        'startdate': 'startDate',
        'enddate': 'endDate',
        'logins': 'logins',
        'searches': 'searches',
        'records': 'records',
        'fc_account': 'fcAccount',
        'maiden_name': 'maidenName',
        'source': 'source',
        'cats_id': 'catsId',
        'maxusers': 'maxUsers',
        'member_status': 'status',
        'address1': 'address1',
        'address2': 'address2',
        'city': 'city',
        'state': 'state',
        'zip': 'zip',
        'country': 'country',
        'phone': 'phone',
        'email': 'email',
        'subplan': 'planId',
        'browser': 'browser',
        'title': 'title',
        'user_profile': 'userProfile',
        'referral': 'referral',
        'options': 'options',
        //'pwd_q': 'securityQuestion',
        //'pwd_a': 'securityAnswer',
        'register_id': 'registrationId',
        //'cs_subscription_id': 'cybersourceSubscriptionsId',
        //'cs_order_no': 'cybersourceOrderNumber',
        'date_created': 'created',
        //'password_enc': 'passwordEncrypted',
        'role_id': 'roleId'
        //'enc_login_phrase': 'encryptedLoginPhrase'
    },
    initialize : function() {
    },
    getFullName : function() {
        return this.firstName + ' ' + this.lastName;
    }
});