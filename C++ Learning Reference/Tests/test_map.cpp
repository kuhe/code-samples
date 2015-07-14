#include "test_map.h"

using Lehr::Map;
using Lehr::List;
using Lehr::Hash;
using Lehr::KeyValuePair;

int test_map() {

    Map<string, string> map;

    map["greeting"] = "hello";

    string test = map["greeting"];

    map["greeting"] = "g\'day";

    string test1 = map["greeting"];

    cout << (test) << endl << (test1) << endl;

    return 0;
};