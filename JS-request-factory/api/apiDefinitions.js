FDO.apiDefinitions = {
    create: {
        subscriptionWithCredit : {
            apiRoute: 'registration/credit-finalize',
            input: {
                registration: FDO.Registration,
                plan: FDO.Plan,
                discount: FDO.Discount
            },
            complexOutput: true,
            output: {
                registration: FDO.Registration,
                plan: FDO.Plan
            }
        },
        subscriptionWithCheck : {
            apiRoute: 'registration/check-finalize',
            input: {
                registration: FDO.Registration,
                member: FDO.Member,
                plan: FDO.Plan,
                discount: FDO.Discount
            },
            complexOutput: true,
            output: {
                registration: FDO.Registration,
                member: FDO.Member,
                plan: FDO.Plan,
                discount: FDO.Discount,
                account: FDO.Account
            }
        }
    },
    read: {
        /**
         * sample entry
         */
        test: {
            /** the route to the controller */
            apiRoute: 'base/example',
            /** the inputs as keys and expected type as values. Input type violations only result in a log notice. */
            input: {
                hello: Number
            },
            /** the output will be cast to this type if a DataObject extending constructor is given, or an array of such */
            output: FDO.Discount
        },
        ssoVerification: {
            apiRoute: 'upgrade/sso-verification',
            complexOutput: true,
            input: {
                hash: String
            },
            output: {
                member: FDO.Member,
                plan: FDO.Plan,
                upgrades: [FDO.Plan]
            }
        },
        states: {
            apiRoute: 'index/states',
            output: [FDO.State]
        },
        countries: {
            apiRoute: 'index/countries',
            output: [FDO.Country]
        },
        username: {
            apiRoute: 'registration/check-username-exists',
            input: {
                username: String
            },
            output: Boolean
        },
        account: {
            apiRoute: 'registration/get-account-information',
            input: {
                registrationId: Number
            },
            complexOutput: true,
            output: {
                account: FDO.Account,
                member: FDO.Member,
                registration: FDO.Registration,
                plan: FDO.Plan
            }
        },
        plans: {
            apiRoute: 'plan/index',
            output: [FDO.Plan]
        },
        planDefinitions: {
            apiRoute: 'plan/definitions',
            output: {}
        },
        legacyPlans: {
            apiRoute: 'plan/legacy',
            input: {
                maxusers: Number,
                months: Number,
                charge: Boolean
            },
            output: [FDO.Plan]
        }
    },
    update: {
        accountUpgrade: {
            apiRoute: 'upgrade/upgrade',
            input: {
                hash: String,
                plan: FDO.Plan
            },
            complexOutput: true,
            output: {
                hopData : Object,
                hopUrl : String
            }
        }
    },
    'delete': {
    }
};