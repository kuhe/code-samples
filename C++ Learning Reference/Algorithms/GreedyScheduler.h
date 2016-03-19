#include "../Data Structures/Student/WeightedJob.h"
#include "_algo_common.h"
#include <algorithm>

#ifndef _CPPREF_GREEDYSCHEDULER_H_
#define _CPPREF_GREEDYSCHEDULER_H_

class GreedyScheduler : public Solver {
public:
    const static string path;
    const static string file;
    vector<string> lines;
    vector<WeightedJob> jobs;

    GreedyScheduler();

    string solve(bool asRatio = false);
    GreedyScheduler& read();
    GreedyScheduler& sort(bool asRatio = false);
    double sum();
};


#endif //_CPPREF_GREEDYSCHEDULER_H_
