#include <iostream>
#include "Tests/test_lists.h"
#include "Tests/test_map.h"
#include "Tests/test_graph.h"
#include "Tests/test_trees.h"

int main() {

    cout << "Hello, World!" << endl << endl;

    cout << "List: ";
    int test = test_lists();
    cout << "Map: ";
    int test2 = test_map();
    cout << "Graph: ";
    int test3 = test_graph();
    cout << "Tree: ";
    int test4 = test_trees();

    cout << "\nYay!" << endl;
    // cin.get();
    return 0;
}