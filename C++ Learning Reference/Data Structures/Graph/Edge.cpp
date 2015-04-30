#include "Edge.h"

Edge::Edge(GraphNode& node1, GraphNode& node2, double weight) : node1(node1), node2(node2), weight(weight) {
    node1.connect(*this);
    node2.connect(*this);
}

GraphNode& Edge::other(GraphNode& node) {
    if (contains(node)) {
        if (node1 == node) {
            return node2;
        }
        return node1;
    }
    return node;
};

bool Edge::contains(GraphNode& node) {
    return node1 == node || node2 == node;
}

bool Edge::operator == (Edge const& edge) {
    return this == &edge;
}