#include "_algo_common.h"
#include "../Data Structures/Library/Graph/_graph_common.h"
#include "../Data Structures/Library/Graph/Graph.h"
#include "../Data Structures/Library/Graph/Tree.h"

#include "../Data Structures/Library/Set/_set_common.h"
#include "../Data Structures/Library/Set/DisjointSetStructure.h"

#ifndef _CPPREF_DISTANCECLUSTERING_H_
#define _CPPREF_DISTANCECLUSTERING_H_


class DistanceClustering : public Solver {
public:
    const static string path;
    const static string file;
    const static string file2;

    DistanceClustering();

    Graph graph;
    Tree tree;
    DisjointSetStructure<GraphNode> unionFind;
    map<int, int> hammingMap;
    vector<int> hammingNodes;
    vector<int> hamming1Xor();
    vector<int> hamming2Xor();

    Tree& kruskal(int stopAt = 1);
    string solve(int stopAt = 1);
    string solveHamming();
    DistanceClustering& read();
    DistanceClustering& readHamming();
    struct by_weight {
        const bool operator() (const Edge* a, const Edge* b) {
            return (*a).weight < (*b).weight;
        }
    };
    unsigned binary_to_decimal(unsigned num) {
        unsigned res = 0;
        for(int i = 0; num > 0; ++i) {
            if ((num % 10) == 1) {
                res += (1 << i);
            }
            num /= 10;
        }
        return res;
    }
};


#endif //_CPPREF_DISTANCECLUSTERING_H_
