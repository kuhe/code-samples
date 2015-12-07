#include <iostream>
#include "Tests/test_lists.h"
#include "Tests/test_map.h"

#include "Data Structures/Student/Graph/_graph_common.h"

using namespace std;

int main() {

    cout << "Hello, World!" << endl;

    int test = test_lists();
    int test2 = test_map();

    Lehr::Graph<int> graph;

    cout << "Yay!" << endl;
    // cin.get();
    return 0;
}