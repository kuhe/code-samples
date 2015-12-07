
#ifndef CPPREF_NODE_H
#define CPPREF_NODE_H

#include "_graph_common.h"

namespace Lehr {
    template <typename T>
    class Node {
        T item;
    public:
        Node() {}
        Node(T item) : item(item) {}

        void connect(Edge<T>* edge) {
            Node<T>* other = edge->other(this);
            if (!connects(other)) {
                nodes.push(other);
            }
            if (!connects(edge)) {
                edges.push(edge);
            }
        }

        List<Node<T>*> nodes;
        List<Edge<T>*> edges;
        bool connects(Node<T>* node) {
            return nodes.contains(node);
        }
        bool connects(Edge<T>* node) {
            return edges.contains(node);
        }
        bool operator == (Node const& node) {
            return this == &node;
        }
    };
}

#endif //CPPREF_NODE_H
