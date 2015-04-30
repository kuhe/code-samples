#include "GraphNode.h"

GraphNode& GraphNode::connect(Edge& edge) {
    Edge* edge_ptr = &edge;
    if (!(std::find(edges.begin(), edges.end(), edge_ptr) != edges.end())) {
        edges.push_back(edge_ptr);
    }
    addNode(edge.other(*this));
    return *this;
};

bool GraphNode::connects(Edge& edge) {
    Edge* edge_ptr = &edge;
    return std::find(edges.begin(), edges.end(), edge_ptr) != edges.end();
};
bool GraphNode::connects(GraphNode& node) {
    GraphNode* node_ptr = &node;
    return std::find(paths.begin(), paths.end(), node_ptr) != paths.end();
};

bool GraphNode::operator == (GraphNode const& node) {
    return this == &node;
};

// protected
GraphNode& GraphNode::addNode(GraphNode& node) {
    GraphNode* node_ptr = &node;
    if (!(std::find(paths.begin(), paths.end(), node_ptr) != paths.end())) {
        paths.push_back(node_ptr);
    }
    return *this;
};