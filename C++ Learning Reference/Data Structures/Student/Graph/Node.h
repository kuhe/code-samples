
#ifndef CPPREF_NODE_H
#define CPPREF_NODE_H

#include "_graph_common.h"

namespace Lehr {
    template <typename T>
    class Node {
        T item;
        List<Node<T>*> visited;
        /**
         * potentially multi-step path exists to the node
         */
        bool hasConnection(Node<T>* node) {
            bool connected;
            if (adjacent(node)) {
                return true;
            }
            // @todo I should use a set instead of a list for visited nodes
            for (int i = 0; i < nodes.count(); i++) {
                Node<T>* n = nodes[i];
                bool test = visited.contains(n);
                if (!visited.contains(n)) {
                    visited.push(n);
                    connected = n->hasConnection(node);
                    if (connected)
                        return true;
                }
            }
            return false;
        }
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

        bool adjacent(Node<T>* node) {
            return *this == *node || nodes.contains(node);
        }
        bool adjacent(Edge<T>* edge) {
            return edges.contains(edge);
        }
        bool connects(Node<T>* node) {
            while (visited.count() > 0) {
                visited.pop();
            }
            bool connects = hasConnection(node);
            return connects;
        }
        /**
         * path exists to a node in the edge
         */
        bool connects(Edge <T> *edge) {
            return connects(edge->left); // the other node is by definition connected.
        }

        bool operator == (Node const& node) {
            return this == &node;
        }
        bool operator == (T const& item) {
            return this->item == &item;
        }
        void operator = (T value) {
            item = value;
        }
    };
}

#endif //CPPREF_NODE_H
