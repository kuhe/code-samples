#include "DistanceClustering.h"

using namespace string_util;

const string DistanceClustering::path = Solver::programRoot() + "Data/";

const string DistanceClustering::file = "algo2_hw2_q1_clustering1.txt";
//const string DistanceClustering::file = "algo2_hw2_q1_test.txt";

const string DistanceClustering::file2 = "algo2_hw2_q1_clustering_big.txt";

DistanceClustering::DistanceClustering() {

}

Tree& DistanceClustering::kruskal(int stopAt) {
    /**
    http://en.wikipedia.org/wiki/DistanceClustering%27s_algorithm

    create a forest F (a set of trees), where each vertex in the graph is a separate tree
    create a set S containing all the edges in the graph
    while S is nonempty and F is not yet spanning
    remove an edge with minimum weight from S
    if that edge connects two different trees, then add it to the forest F, combining two trees into a single tree
    At the termination of the algorithm, the forest forms a minimum spanning forest of the graph. If the graph is
     connected, the forest has a single component and forms a minimum spanning tree.
     */
    Set<Edge>* mstEdges_ptr = new Set<Edge>;
    Set<Edge>& mstEdges = *mstEdges_ptr;
    for (auto &node : graph.nodes) {
        unionFind.make(*node);
    }

    std::sort(graph.edges.begin(), graph.edges.end(), by_weight());
    for (auto &edge : graph.edges) {
        Edge& edgeRef = *edge;
        GraphNode& node1 = edgeRef.node1;
        GraphNode& node2 = edgeRef.node2;

        Set<GraphNode>& set1 = unionFind.find(node1);
        Set<GraphNode>& set2 = unionFind.find(node2);

        if (set1 != set2) {
            mstEdges.add(*edge);
            unionFind.merge(unionFind.find(node1), unionFind.find(node2));
        }

        if (unionFind.sets.size() <= stopAt) {
            break;
        }
    }

    for (auto &edge : mstEdges.elements) {
        tree.addEdge(*edge);
    }
    delete mstEdges_ptr;
    return tree;
}

/**
 * For our particular solution, it is equivalent to stopping Kruskal's at K disjoint sets remaining.
 */
string DistanceClustering::solve(int stopAt) {
    read().kruskal(stopAt);
    std::sort(graph.edges.begin(), graph.edges.end(), by_weight());

    if (tree.edges.size() > 0) {
        for (auto &edge : graph.edges) {
            if (unionFind.find((*edge).node1) != unionFind.find((*edge).node2)) {
                return to_string((*edge).weight);
            }
        }
    }
    return "Uh oh";
}

vector<int> DistanceClustering::hamming1Xor() {
    vector<int> container;
    for (int i = 0; i < )
}

vector<int> DistanceClustering::hamming1Xor() {

}

string DistanceClustering::solveHamming() {
    readHamming();
    int candidateNodeCount = 200000;
    for (auto &node : hammingNodes) {
        vector<int> hamming2, hamming1;
        for (auto &one : hamming1Xor()) {

        }
    }
    return "";
}

DistanceClustering &DistanceClustering::read() {
    ifstream readFile;
    readFile.open(path + file);

    if (readFile.is_open()) {
        for (std::string line; std::getline(readFile, line); ) {
            vector<string> lineVector = split(line, ' ');
            if (lineVector.size() == 1) {
                unsigned int nodeCount = (unsigned int) stoi(lineVector.at(0));
                graph.nodes.reserve(nodeCount);
                graph.edges.reserve((nodeCount*(nodeCount-1)/2));
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
}

DistanceClustering &DistanceClustering::readHamming() {
    ifstream readFile;
    readFile.open(path + file2);

    if (readFile.is_open()) {
        for (string line; getline(readFile, line); ) {
            vector<string> lineVector = split(line, ' ');
            char binary = stoi(string_util::join(lineVector));
            hammingMap[binary] = binary;
            hammingNodes.push_back(binary);
        }
    }
    return *this;
}