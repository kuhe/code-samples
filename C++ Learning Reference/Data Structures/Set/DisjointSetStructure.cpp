#include "DisjointSetStructure.h"

template <typename T>
Set<T>& DisjointSetStructure<T>::find(T& element) {
    return *parents[&element];
}

template <typename T>
DisjointSetStructure<T>& DisjointSetStructure<T>::remove(Set<T>& set) {
    Set<T>* ptr = &set;
    sets.erase(std::remove(sets.begin(), sets.end(), ptr));
    delete ptr;
    return *this;
}

template <typename T>
DisjointSetStructure<T>& DisjointSetStructure<T>::remove(Set<T>& a, Set<T>& b) {
    remove(a);
    remove(b);
    return *this;
}

template <typename T>
Set<T> DisjointSetStructure<T>::merge(Set<T>& a, Set<T>& b) {
    Set<T>* set_ptr = new Set<T>;
    Set<T>& set = *set_ptr;
    for (auto &element : a.elements) {
        parents[element] = set_ptr;
        set.add(*element);
    }
    for (auto &element : b.elements) {
        parents[element] = set_ptr;
        set.add(*element);
    }
    remove(a, b);
    sets.push_back(set_ptr);
    return set;
}

template <typename T>
Set<T>& DisjointSetStructure<T>::make(T& element) {
    Set<T>* ptr = new Set<T>;
    Set<T>& set = *ptr;
    set.add(element);
    parents[&element] = ptr;
    sets.push_back(ptr);
    return set;
}

template class DisjointSetStructure<GraphNode>;