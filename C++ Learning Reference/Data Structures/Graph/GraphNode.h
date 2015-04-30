#ifndef _CPPREF_GRAPHNODE_H_
#define _CPPREF_GRAPHNODE_H_

#include "_graph_common.h"
#include "Edge.h"

using namespace std;

class GraphNode {
public:
    vector<GraphNode*> paths;
    vector<Edge*> edges;
    GraphNode& connect(Edge& edge);
    bool connects(Edge& edge);
    bool connects(GraphNode& node);
    bool operator == (GraphNode const& node);
protected:
    GraphNode& addNode(GraphNode& node);
};


#endif //_CPPREF_GRAPHNODE_H_
