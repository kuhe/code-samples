var User = Namespace.User = (function(jQuery) {
    var $ = jQuery;
    var User = function(data) {
        DataObject.prototype.initialize.call(this, data);
    };
    User.prototype = $.extend(new DataObject, {
        constructor : User,
        identifier : 'User',
        dataProperties : {
            // canonical
            'id': 'id',
            '_id': '_id',
            'email': 'email',
            'username': 'username',
            'password': 'password'
            
        },
        init : function(data) {
            if (data == 'dummy') {
                
            } else {

            }
        }
    });
    return User;
})($);
