
#ifndef CPPREF_GRAPH_H
#define CPPREF_GRAPH_H

#include "_graph_common.h"

namespace Lehr {
    template <typename T>
    class Graph {
    protected:
        List<Node<T>*> nodes;
        List<Edge<T>*> edges;
    public:
        Graph& addNode(Node<T>* node) {
            if (!nodes.contains(node)) {
                nodes.push(node);
            }
            return *this;
        }
        Graph& addEdge(Node<T>* a, Node<T>* b, int edgeWeight=0) {
            if (!nodes.contains(a)) {
                nodes.push(a);
            }
            if (!nodes.contains(b)) {
                nodes.push(b);
            }
            Edge<T> edge(a, b);
            edge.weight = edgeWeight;
            edges.push(&edge);
            return *this;
        }
        Graph& addEdge(Edge<T>* edge) {
            Node<T>* a, * b;
            a = edge->left;
            b = edge->right;
            if (!nodes.contains(a)) {
                nodes.push(a);
            }
            if (!nodes.contains(b)) {
                nodes.push(b);
            }
            if (!edges.contains(edge)) {
                edges.push(edge);
            }
            return *this;
        }
        bool contains(Node<T>* node) {
            return nodes.contains(node);
        }
        bool contains(Edge<T>* edge) {
            return edges.contains(edge);
        }
        static int main_test() {
            Graph<int> graph;
            Node<int> n1, n2;
            Edge<int> edge(&n1, &n2);

            graph.addEdge(&n1, &n2);
            graph.addEdge(&edge);

            // wip todo

            bool test1 = n1.connects(&n2);
            bool test2 = n2.connects(&n1);
            bool test3 = n1.connects(&edge);

            return 0;
        }
    };
}

#endif //CPPREF_GRAPH_H
