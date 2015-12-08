#include "test_graph.h"

template <typename T, typename V>
void console_test(T a, V b) {
    if (a == b) {
        cout << ".";
    } else {
        cout << a << " ! " << b << endl;
    }
}
void console_test(bool evaluation) {
    if (evaluation) {
        cout << ".";
    } else {
        cout << " F " << endl;
    }
}
template void console_test<string, string>(string a, string b);

using Lehr::Graph;
using Lehr::Node;
using Lehr::Edge;

int test_graph() {
    Graph<int> graph;
    Node<int> n1, n2, n3, n4;
    Edge<int> edge(&n1, &n4);

    graph.addEdge(&n1, &n2);
    graph.addEdge(&edge);

    graph.connect(&n1, &n3);

    bool test1 = n1.adjacent(&n2);
    bool test2 = n2.adjacent(&n1);
    bool test3 = n1.adjacent(&edge);
    bool test4 = n3.adjacent(&n1);
    bool test5 = n4.adjacent(&n1);
    bool test6 = !n4.adjacent(&n2);

    console_test(test1);
    console_test(test2);
    console_test(test3);
    console_test(test4);
    console_test(test5);
    console_test(test6);

    return 0;
};

