#include <iostream>
#include "Tests/test_lists.h"
#include "Tests/test_map.h"
#include "Tests/test_graph.h"

using std::cout;
using std::endl;
using std::cin;

int main() {

    cout << "Hello, World!" << endl;

    int test = test_lists();
    int test2 = test_map();
    int test3 = test_graph();

    cout << "\nYay!" << endl;
    // cin.get();
    return 0;
}