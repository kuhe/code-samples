#include <string>
#include <iostream>
#include <assert.h>
#include "test_structures.h"
#include "../Utilities/_std_symbols.h"

template <typename T, typename V>
void console_test(T a, V b) {
    cout << a << " " << b << endl;
    assert(a == b);
}
template void console_test<string, string>(string a, string b);


int test_structures() {

    string a = "hello.",
           b = "how.",
           c = "are.",
           d = "you.";


    List<string> lln(a);
    List<string> lln2(lln, b);
    List<string> lln3(lln2, c);
    List<string> lln4(d);
    lln.push(lln4);
    List<string> lln5(d);
    lln.push(lln5);
    lln.push(d);
    lln.push(d);

    cout << "----" << endl;
    lln.print();
    cout << "----" << endl;

    console_test(lln[0].item, a);
    console_test(lln.slice(1).item, b);
    console_test(lln[2].item, c);
    console_test(lln[3].item, d);
    console_test(lln[4].item, d);
    console_test(lln[5].item, d);
    console_test(lln[6].item, d);

    console_test((*lln.end()).item, (string) d);

    lln.shift();
    console_test(lln[0].item, b);

    return 0;
};

