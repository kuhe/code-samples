
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
            if (!adjacent(other)) {
                nodes.push(other);
            }
            if (!adjacent(edge)) {
                edges.push(edge);
            }
        }

        List<Node<T>*> nodes;
        List<Edge<T>*> edges;

        bool adjacent(Node<T> *node) {
            return *this == *node || nodes.contains(node);
        }
        bool adjacent(Edge <T> *edge) {
            return edges.contains(edge);
        }
        /**
         * path exists to the node
         */
        bool connects(Node<T>* node) {
            // todo
            return false;
        }
        /**
         * path exists to a node in the edge
         */
        bool connects(Edge <T> *edge) {
            // todo
            return false;
        }

        bool operator == (Node const& node) {
            return this == &node;
        }
        void operator = (T value) {
            item = value;
        }
    };
}

#endif //CPPREF_NODE_H
