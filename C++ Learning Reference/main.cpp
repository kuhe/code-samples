#include <iostream>
#include "Tests/test_structures.h"
#include "Tests/test_map.h"

using namespace std;

int main() {

    cout << "Hello, World!" << endl;

    int test = test_structures();
    int test2 = test_map();

    cout << "Yay!" << endl;
    // cin.get();
    return 0;
}