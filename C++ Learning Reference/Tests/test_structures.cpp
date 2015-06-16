#include <string>
#include <iostream>
#include "test_structures.h"

using namespace std;

int test_structures() {

    string a = "abc",
           b = "def";

    LinkedList<string> lln(a);
    LinkedList<string> lln2(&lln, b);
    LinkedList<string> lln3(b, &lln2);

    cout << lln.next->data << endl;

    return 0;
};

