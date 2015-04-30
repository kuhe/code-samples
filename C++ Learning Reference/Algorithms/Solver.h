#include <string>

#ifndef _CPPREF_SOLVER_H_
#define _CPPREF_SOLVER_H_

using namespace std;

class Solver {
public:
    const static string programRoot(void) {
        return "C:/xampp/htdocs/wegukgi/cppRef/";
    };
    const static string path;
    const static string file;

    virtual string solve() {return "";};
    virtual Solver& read() {return *this;};
};

//string Solver::programRoot = "C:/xampp/htdocs/wegukgi/cppRef/";
//string Solver::programRoot = "C:/wamp/www/github/wegukgi/cppRef/";
//string Solver::programRoot = "C:/www/wegukgi/cppRef/";

#endif //_CPPREF_SOLVER_H_
