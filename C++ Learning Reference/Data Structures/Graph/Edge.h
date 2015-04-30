#ifndef _CPPREF_EDGE_H_
#define _CPPREF_EDGE_H_

#include "_graph_common.h"
#include "GraphNode.h"

using namespace std;

class Edge {
public:
    double weight;
    GraphNode& node1;
    GraphNode& node2;
    Edge(GraphNode& node1, GraphNode& node2, double weight = 0);
    GraphNode& other(GraphNode& node);
    bool contains(GraphNode& node);
    bool operator == (Edge const& edge);
};


#endif //_CPPREF_EDGE_H_
