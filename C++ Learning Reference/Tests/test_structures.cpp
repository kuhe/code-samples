#include <string>
#include <iostream>
#include <assert.h>
#include "test_structures.h"
#include "../Utilities/_std_symbols.h"

template <typename T, typename V>
void console_test(T a, V b) {
    cout << a << " " << b << endl;
}
template void console_test<string, string>(string a, string b);

using Lehr::List;
using Lehr::ArrayList;

int test_structures() {

    string a = "hello.",
           b = "how.",
           c = "are.",
           d = "you.",
           e = "my.",
           f = "name.",
           g = "is.";

    List<string> lln;
    List<string> lln2;
//    ArrayList<string> lln;
//    ArrayList<string> lln2;
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

    console_test(a_test, a);
    console_test(b_test, b);
    console_test(f_test, f);
    console_test(g_test, g);

    lln.unshift(b_test);
    lln.unshift(a_test);
    lln.push(f_test);
    lln.push(g_test);

    lln.excise(2, 4);
    console_test(lln[2], f);

    console_test(lln.count(), 4);

    lln2.push(c);
    lln2.push(d);
    lln2.push(e);
    lln.splice(2, lln2);
    console_test(lln.count(), 7);
    console_test(lln[2], c);

    lln.splice(7, e);
    console_test(lln[7], e);
    console_test(lln.count(), 8);

    return 0;
};

