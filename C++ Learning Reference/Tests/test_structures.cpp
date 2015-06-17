#include <string>
#include <iostream>
#include <assert.h>
#include "test_structures.h"

using namespace std;
template <typename T, typename V>
void console_test(T a, V b) {
    cout << a << " " << b << endl;
    assert(a == b);
}
template void console_test<string, string>(string a, string b);


int test_structures() {

    string a = "hello",
           b = "how",
           c = "are",
           d = "you";


    LinkedList<string> lln(a);
    LinkedList<string> lln2(lln, b);
    LinkedList<string> lln3(lln2, c);
    LinkedList<string> lln4(lln3, d);
//
    console_test(lln.next->data, b);
//    LinkedList<string> test = lln[0];
    console_test(lln[0].data, a);
    console_test(lln[1].data, b);
    console_test(lln[2].data, c);
    console_test(lln[3].data, d);
    console_test((*lln.end()).data, (string) d);

    return 0;
};

