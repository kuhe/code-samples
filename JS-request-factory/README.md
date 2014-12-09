Code Sample (JavaScript)


JS-request-factory
==================

Set an object describing the requests you want to make, and receive a group of easily invoked jqXHR requests cast to a front end object data model.

    All functions produced from instructions object through a single request model.
    JSON transfer to and from backend.
    Result can be cast to desired client model class.
    Sequential or object arguments.
    Client side cache options (see old version).
    Singleton
    Support for synchronizing multiple request callbacks.
    

Example Instruction Input:

    requests = {
      read : {
        user : {
          help : {
            input : {
              id : 1
            },
            output : User
          }
        },
        item : {
          ...
        }
      },
      update : {
        ...
      }
    }
    
Example Api created:

    (new Api).get.user('me@mail.com', [optional callback as last argument])
    (new Api).get.item(1)
    
    api = new Api;
    api.get([
      ['user', {email: 'me@gmail.com'}],
      ['item' , {id: 1}],
      callback that fires when both requests finish, that has an array of the results as argument
    ])
