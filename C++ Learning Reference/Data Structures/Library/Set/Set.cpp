#include "Set.h"

template <typename T>
Set<T>& Set<T>::add(T& element) {
    T* element_ptr = &element;
    elements.push_back(element_ptr);
    return *this;
}

template <typename T>
bool Set<T>::contains(T& element) {
    T* element_ptr = &element;
    return std::find(elements.begin(), elements.end(), element_ptr) != elements.end();
}

template <typename T>
bool Set<T>::operator == (Set<T> const& set) {
    return this == &set;
};

template <typename T>
bool Set<T>::operator != (Set<T> const& set) {
    return !this->operator==(set);
};


template class Set<GraphNode>;
template class Set<Edge>;