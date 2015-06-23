Code Sample (JavaScript)


JS-request-factory
==================

Set an object describing the requests you want to make, and receive a group of easily invoked jqXHR/$http.post requests cast to a front end object data model.

    All functions produced from apiDefinitions (i.e. ajax signatures) object through a single request model.
    JSON transfer to and from backend.
    Result can be cast to desired client model class.
    Sequential or object arguments.
    Client side cache options (see old version).
    Support for synchronizing multiple request callbacks.

Example Signature Configuration object:

    requests = {
      read : {
        user : {
          input : {
            email : String
          },
          output : User
        },
        item : {
          input : {
            id : Number
          },
          output : User
        }
      },
      update : {
        ...
      }
    }

Invoking (new Api) then caches the methods generated.

Example, usage of generated api methods:

    // sequential arguments
    (new Api).get.user('me@mail.com', function(user) {
        assert(user instanceof User === true)
    })
    // or object argument
    (new Api).get.user({email: 'me@mail.com'}, function(user) {
        assert(user instanceof User === true)
    })

    // without callback
    (new Api).get.item(1)
    (new Api).get.item({id : 1})

    // unified callback for multiple asynchronous requests
    (new Api).get([
      ['user', {email: 'me@gmail.com'}],
      ['item' , {id: 1}],
      function(results) {
        controller.user = results.user;
        controller.item = results.item;
        if (controller.user instanceof User && controller.item instanceof Item) {
          ...
        }
      }
    ])
