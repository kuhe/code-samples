/**
 * calls defined here will be cast to the appropriate types upon output, and warn if input types mismatch
 */
NS.apiDefinitions = {
    create: {
    },
    read: {
        /**
         * sample entries
         */
        test: {
            /** the route to the backend controller or api */
            apiRoute: 'base/example',
            /** the inputs as keys and expected type as values. Input type violations only result in a log notice. */
            input: {
                hello: Number
            },
            /** the output will be cast to this type if a DataObject extending constructor is given, or an array of such */
            output: NS.Item
        },
        test2: {
            apiRoute: 'some/path',
            input: {
                input1: Number,
                anyInputName: String,
                input3: Boolean,
                input4: Array,
                item: NS.Item
            },
            complexOutput: true,
            output: {
                someData: Array,
                returnItems: [NS.Item] // return an array of this type
            }
        }
    },
    update: {
    },
    'delete': {
    }
};