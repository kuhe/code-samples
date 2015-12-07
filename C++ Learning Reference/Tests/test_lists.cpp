#include <string>
#include <iostream>
#include "test_lists.h"
#include "../Utilities/_std_symbols.h"

template <typename T, typename V>
void console_test(T a, V b) {
    if (a == b) {
        cout << ".";
    } else {
        cout << a << " ! " << b << endl;
    }
}
template void console_test<string, string>(string a, string b);

using Lehr::List;
using Lehr::ArrayList;

int test_lists() {

    string a = "hello.",
           b = "how.",
           c = "are.",
           d = "you.",
           e = "my.",
           f = "name.",
           g = "is.",
           h = "indexTest";

//    List<string> lln, lln2;
    ArrayList<string> lln, lln2;

    lln.push(c);
    lln.push(d);
    lln.push(e);
    lln.push(f);
    lln.push(g);
    lln.unshift(b);
    lln.unshift(a);

    console_test(lln[0], a);
    console_test(lln[1], b);
    console_test(lln[2], c);
    console_test(lln[3], d);
    console_test(lln[4], e);
    console_test(lln[5], f);
    console_test(lln[6], g);

    string a_test = lln.shift();
    string b_test = lln.shift();
    string g_test = lln.pop();
    string f_test = lln.pop();

    // [c, d, e]

    console_test(a_test, a);
    console_test(b_test, b);
    console_test(f_test, f);
    console_test(g_test, g);

    lln.unshift(b_test);
    lln.unshift(a_test);
    lln.push(f_test);
    lln.push(g_test);

    // [a, b, c, d, e, f, g]

    lln.excise(2, 4);
    // [a, b, f, g]
    console_test(lln[2], f);
    console_test(lln[3], g);

    console_test(lln.count(), 4);

    lln2.push(c);
    lln2.push(d);
    lln2.push(e);
    lln.splice(2, lln2);
    // [a, b, c, d, e, f, g]

    console_test(lln.count(), 7);
    console_test(lln[2], c);
    console_test(lln[6], g);

    lln.splice(7, a);
    // [a, b, c, d, e, f, g, a]
    console_test(lln[7], a);
    console_test(lln[6], g);

    lln.push(h);
    lln.push(h);
    // [a, b, c, d, e, f, g, a, h, h]
    console_test(lln[8], h);

    string test0 = lln[0];
    string test5 = lln[5];
    string test6 = lln[6];
    string test7 = lln[7];
    string test8 = lln[8];
    string test9 = lln[9];

    console_test(lln[7], a);
    console_test(lln[6], g);
    console_test(0, lln.indexOf(a));

    console_test(lln.count(), 10);

    return 0;
};
