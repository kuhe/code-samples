#include "Graph.h"

Graph& Graph::addEdge(GraphNode& a, GraphNode& b, int edgeWeight) {
    if (!contains(a)) {
        nodes.push_back(&a);
    }
    if (!contains(b)) {
        nodes.push_back(&b);
    }
    Edge edge(a, b, edgeWeight);
    a.connect(edge);
    b.connect(edge);
    edges.push_back(&edge);
    return *this;
};
Graph& Graph::addEdge(Edge& edge) {
    if (!contains(edge.node1)) {
        nodes.push_back(&edge.node1);
    }
    if (!contains(edge.node2)) {
        nodes.push_back(&edge.node2);
    }
    edges.push_back(&edge);
    return *this;
};

bool Graph::contains(GraphNode& node) {
    GraphNode* node_ptr = &node;
    return std::find(nodes.begin(), nodes.end(), node_ptr) != nodes.end();
};

bool Graph::contains(Edge& edge) {
    Edge* edge_ptr = &edge;
    return std::find(edges.begin(), edges.end(), edge_ptr) != edges.end();
};