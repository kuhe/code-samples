FDO.Account = function(data) {
    this.init(data)
};

FDO.Account.prototype = angular.extend(new FDO.DataObject, {
    identifier : 'Account',
    constructor : FDO.Account,
    columns : {
        acct_id: 'id',
        member_id: 'memberId',
        //cc_num: 'creditCardNumber',
        cc_exp: 'creditCardExpiration',
        acct_status: 'status',
        name: 'name',
        address: 'address',
        city: 'city',
        state: 'state',
        zip: 'zip',
        //cc_enc: 'creditCardEncrypted',
        //cc_md5: 'creditCardMd5',
        cc_last4: 'creditCardLast4',
        //cc_first4: 'creditCardFirst4',
        //cybersource_upload_status: 'cybersourceUploadStatus',
        cc_type: 'creditCardType',
        billTo_city: 'billingCity',
        billTo_company: 'billingCompany',
        billTo_country: 'billingCountry',
        billTo_email: 'billingEmail',
        billTo_firstName: 'billingFirstName',
        billTo_lastName: 'billingLastName',
        billTo_phoneNumber: 'billingPhone',
        billTo_postalCode: 'billingZip',
        billTo_state: 'billingState',
        billTo_street1: 'billingAddress',
        billTo_Street2: 'billingAddress2'
        //ignore_AVS: 'ignoreAvs',
        //is_decrypted: 'isDecrypted'
    },
    initialize : function() {
    },
    getCreditCardExpiration : function() {
        var datePieces = s.account.creditCardExpiration.split(' ');
        var n = 3;
        var date = new Date(datePieces.slice(0, n).join(' '));

        var monthNames = [
            'January', 'February', 'March',
            'April', 'May', 'June',
            'July', 'August', 'September',
            'October', 'November', 'December'
        ];
        if (date instanceof Date) {
            return (monthNames[date.getMonth()]) + ' ' + date.getFullYear();
        }
    }
});