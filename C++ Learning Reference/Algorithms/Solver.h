#include <string>
#include <vector>

#ifndef _CPPREF_SOLVER_H_
#define _CPPREF_SOLVER_H_

using std::string;

class Solver {
public:
    const static string programRoot(void) {
        return "C:/wamp/www/github/code-samples/C++ Learning Reference/";
    };
    const static string path;
    const static string file;

    virtual string solve() {return "";};
    virtual Solver& read() {return *this;};
};

#endif //_CPPREF_SOLVER_H_
