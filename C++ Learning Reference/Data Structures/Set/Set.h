#include "../Graph/_graph_common.h"
#include "../Graph/GraphNode.h"
#include "../Graph/Edge.h"

#include "_set_common.h"

#ifndef CPPREF_SET_H
#define CPPREF_SET_H

template <typename T>
class Set {
public:
    vector<T*> elements;
    Set& add(T& element);
    bool contains(T& element);
    bool operator == (Set<T> const& set);
    bool operator != (Set<T> const& set);
};

#endif //CPPREF_SET_H
