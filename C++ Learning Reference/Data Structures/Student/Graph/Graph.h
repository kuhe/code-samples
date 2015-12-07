
#ifndef CPPREF_GRAPH_H
#define CPPREF_GRAPH_H

#include "_graph_common.h"
#include "../List/List.h"

namespace Lehr {
    template <typename T>
    class Graph {
    protected:
        struct Node {
            friend class Graph<T>;
            T item;
            Node() {};
            Node(T item) : item(item) {};
            void operator =(T item) {
                this->item = item;
            };
        };
        struct Edge {
            friend class Graph<T>;
            Node* left;
            Node* right;
            Edge() {};
            Edge(Node* l, Node* r) {
                left = l;
                right = r;
            }
        };
    public:
        List<Node*> nodes;
        List<Edge*> edges;
        Graph& addEdge(Node& a, Node& b, int edgeWeight) {
            return *this;
        }
        Graph& addEdge(Edge& edge) {
            return *this;
        }
        bool contains(Node& node) {
            return 0;
        }
        bool contains(Edge& edge) {
            return 0;
        }
        int main_test() {
            Graph graph;
            return 0;
        }
    };
}

#endif //CPPREF_GRAPH_H
