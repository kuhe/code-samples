#include "GreedyScheduler.h"

using namespace string_util;

const string GreedyScheduler::path = Solver::programRoot() + "Data/";

const string GreedyScheduler::file = "algo2_hw1_q1.txt";
//const string GreedyScheduler::file = "algo2_hw1_q1_test.txt";


vector<string> lines;
vector<WeightedJob> jobs;

GreedyScheduler::GreedyScheduler() {
    read();
}
string GreedyScheduler::solve(bool asRatio) {
    string solution = to_string(sort(asRatio).sum());
    return solution;
};
GreedyScheduler& GreedyScheduler::sort(bool asRatio) {
    if (asRatio) {
        std::sort(jobs.begin(), jobs.end(), WeightedJob::higherPriorityRatio);
    } else {
        std::sort(jobs.begin(), jobs.end(), std::greater<WeightedJob>());
    }
    return *this;
};
double GreedyScheduler::sum() {
    double sum = 0, runningTime = 0;
    for (auto &job : jobs) {
        double completion = job.length + runningTime;
        runningTime += job.length;
        sum += job.weight * completion;
    }
    return sum;
};
GreedyScheduler& GreedyScheduler::read() {
    lines.reserve(10000); // let's pretend this helps
    jobs.reserve(10000);
    ifstream readFile;
    readFile.open(path + file);
    if (readFile.is_open()) {
        for (std::string line; std::getline(readFile, line); ) {
            lines.push_back(line);
            vector<string> v = split(line, ' ');
            if (v.size() > 1) {
                WeightedJob job(v.at(0), v.at(1));
                jobs.push_back(job);
            }
        }
    }
    return *this;
}
