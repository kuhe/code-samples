#ifndef _CPPREF_GRAPH_H_
#define _CPPREF_GRAPH_H_

#include "_graph_common.h"
#include "Edge.h"
#include "GraphNode.h"

using namespace std;

class Graph { // undirected
public:
    vector<GraphNode*> nodes;
    vector<Edge*> edges;
    Graph& addEdge(GraphNode& a, GraphNode& b, int edgeWeight);
    Graph& addEdge(Edge& edge);
    bool contains(GraphNode& node);
    bool contains(Edge& edge);
};


#endif //_CPPREF_GRAPH_H_
