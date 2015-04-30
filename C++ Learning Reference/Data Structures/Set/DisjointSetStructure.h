#include "../Graph/_graph_common.h"
#include "Set.h"

#ifndef CPPREF_DISJOINTSET_H
#define CPPREF_DISJOINTSET_H

template <typename T>
class DisjointSetStructure {
public:
    vector<Set<T>*> sets;

    map<T*, Set<T>*> parents;

    Set<T>& find(T& element);
    DisjointSetStructure& remove(Set<T>& set);
    DisjointSetStructure& remove(Set<T>& a, Set<T>& b);

    Set<T> merge(Set<T>& a, Set<T>& b);
    Set<T>& make(T& element);
};


#endif //CPPREF_DISJOINTSET_H
