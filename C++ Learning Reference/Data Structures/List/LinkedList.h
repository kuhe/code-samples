#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include <string>
using namespace std;

template <typename T>

class LinkedList {
public:
    T data;
    LinkedList* next;
    LinkedList();
    LinkedList(LinkedList* previous);
    LinkedList(T nodeData);
    LinkedList(T nodeData, LinkedList* previous);
    LinkedList(LinkedList* previous, T nodeData);
};

template class LinkedList<string>;
template class LinkedList<int>;
template class LinkedList<double>;

#endif //CPPREF_LINKEDLIST_H
