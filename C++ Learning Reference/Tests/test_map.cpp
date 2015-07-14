#include "test_map.h"

using Lehr::Map;
using Lehr::List;
using Lehr::Hash;
using Lehr::KeyValuePair;

template <typename T, typename V>
void test(T a, V b) {
    cout << a << " " << b << endl;
}
template void test<string, string>(string a, string b);

int test_map() {
    string a = "hello.",
           b = "how.",
           c = "are.",
           d = "you.",
           e = "my.",
           f = "name.",
           g = "is.",
           t1, t2;

    /** test collision */
    Map<string, string> map(1);
    test(map.hash(a), map.hash(a));
    test(map.hash(b), map.hash(b));
    test(map.hash(g), map.hash(g));
    map["greeting"] = "hello";
    map["phrase"] = "how are you";
    map["phrase_two"] = "but I\'m hopin\' all the same";
    t1 = map["greeting"];
    t2 = map["greeting"];
    map["phrase"] = "I don\'t even know your name";
    test(t1, t2);
    t2 = "I don\'t even know your name";
    test(map["phrase"], t2);

    /** test with higher size */
    Map<string, string> map2(1024);
    map2["greeting"] = "hello";
    map2["phrase"] = "how are you";
    map2["phrase_two"] = "but I\'m hopin\' all the same";
    t1 = map2["greeting"];
    t2 = map2["greeting"];
    map2["phrase"] = "I don\'t even know your name";
    test(t1, t2);
    t2 = "I don\'t even know your name";
    test(map["phrase"], t2);

    return 0;
};