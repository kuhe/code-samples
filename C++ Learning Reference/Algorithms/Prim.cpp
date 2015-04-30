#include "Prim.h"

const string Prim::path = Solver::programRoot() + "Data/";

const string Prim::file = "algo2_hw1_q3_edges.txt";
//const string Prim::file = "algo2_hw1_q3_test.txt";


Prim::Prim(Graph graph, Tree tree) : graph(graph), tree(tree) {

};
string Prim::solve() {
    read();

    /** Wikipedia:
    * Initialize a tree with a single vertex, chosen arbitrarily from the graph.
      Grow the tree by one edge: of the edges that connect the tree to vertices not yet in the tree,
          find the minimum-weight edge, and transfer it to the tree.
      Repeat step 2 (until all vertices are in the tree).
    */

    for (auto &node : graph.nodes) {
        findMinEdgesFrom(node);
    }

    while(graph.edges.size() > 0) delete graph.edges.back(), graph.edges.pop_back();
    while(graph.nodes.size() > 0) delete graph.nodes.back(), graph.nodes.pop_back();

    return to_string(treeCost);
};
Edge& Prim::findMinEdgesFrom(GraphNode* node) {
    Edge*& minEdge_ptr = (*node).edges.at(0);
    Edge& edge_ref = *minEdge_ptr;

    tree.nodes.push_back(node);

    while (tree.nodes.size() < graph.nodes.size()) {
        bool edgeFound = false;
        vector<Edge*>* candidateEdges = new vector<Edge*>();
        for (auto &edge : graph.edges) {
            if (!tree.contains(*edge) and (tree.contains((*edge).node1) or tree.contains((*edge).node2))) {
                if (!tree.contains((*edge).node1) or !tree.contains((*edge).node2)) {
                    minEdge_ptr = edge;
                    (*candidateEdges).push_back(edge);
                }
            }
        }
        for (auto &edge : *candidateEdges) {
            if ((*edge).weight <= (*minEdge_ptr).weight) {
                edgeFound = true;
                minEdge_ptr = edge;
                if (tree.contains((*edge).node1)) {
                    node = &(*edge).node2;
                } else {
                    node = &(*edge).node1;
                }
            }
        }
        delete candidateEdges;
        if (edgeFound) {
            tree.nodes.push_back(node);
            tree.edges.push_back(minEdge_ptr);
            treeCost += (*minEdge_ptr).weight;
            //cout << "adding node with address " << static_cast<void*>(node) << endl;
            //cout << "adding edge with weight " + to_string((*minEdge_ptr).weight) + "\n";
        }
    }

    return *minEdge_ptr;
};

using namespace string_util;

Prim& Prim::read() {
    ifstream readFile;
    readFile.open(path + file);
    if (readFile.is_open()) {
        for (std::string line; std::getline(readFile, line); ) {
            vector<string> lineVector = split(line, ' ');
            if (lineVector.size() == 2) {
                unsigned int nodeCount = (unsigned int) stoi(lineVector.at(0));
                graph.nodes.reserve(nodeCount);
                graph.edges.reserve((unsigned int) stoi(lineVector.at(1)));
                for (int n = 1; n <= nodeCount; n++) {
                    GraphNode* node_ptr = new GraphNode();
                    graph.nodes.push_back(node_ptr);
                }
            } else if (lineVector.size() == 3) {
                int node1Id = stoi(lineVector.at(0)) - 1;
                int node2Id = stoi(lineVector.at(1)) - 1;
                double edgeWeight = stod(lineVector.at(2));
                Edge* edge_ptr = new Edge(*graph.nodes.at((unsigned int) node1Id), *graph.nodes.at((unsigned int) node2Id), edgeWeight);
                graph.edges.push_back(edge_ptr);
            }
        }
    }
    return *this;
};