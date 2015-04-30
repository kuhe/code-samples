#include "_algo_common.h"
#include "../Data Structures/Graph/_graph_common.h"
#include "../Data Structures/Graph/Graph.h"
#include "../Data Structures/Graph/Tree.h"


#ifndef _CPPREF_PRIM_H_
#define _CPPREF_PRIM_H_

using namespace std;

class Prim : public Solver {
public:
    const static string path;
    const static string file;

    Prim(Graph graph = Graph(), Tree tree = Tree());

    Graph& graph;
    Tree& tree;
    double treeCost;

    string solve();
    Edge& findMinEdgesFrom(GraphNode* node);
    Prim& read();
};


#endif //_CPPREF_PRIM_H_
