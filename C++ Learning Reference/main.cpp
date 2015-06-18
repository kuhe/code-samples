#include <iostream>
#include <string>
#include <assert.h>
#include "Algorithms/GreedyScheduler.h"
#include "Algorithms/Prim.h"
#include "Algorithms/DistanceClustering.h"
#include "Tests/test_structures.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    int test = test_structures();
    assert(0 == test);

    bool runOldSolutions = 0;
    if (runOldSolutions) {
        GreedyScheduler gs;
        string solution1 = gs.solve();
        cout << "Weight - length: " + solution1 << endl;
        string solution2 = gs.solve(true);
        cout << "weight / length: " + solution2 << endl;
        Prim prim;
        string solution3 = prim.solve();
        cout << "Prim's: " + solution3 << endl;
    }
    bool runIncompleteSolutions = 0;
    if (runIncompleteSolutions) {
        DistanceClustering dc;
        string solution4 = dc.solve(4);
        cout << "Distance clustering: " + solution4 << endl;
        DistanceClustering dc2;
        string solution5 = dc2.solveHamming();
        cout << "Large Hamming cluster: " + solution5 << endl;
    }

    cout << "Yay..." << endl;
    // cin.get();
    return 0;
}