#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include <string>
using namespace std;

template <typename T>

class LinkedList {
public:
    T data;
    LinkedList<T>* next;
    LinkedList<T>();
    LinkedList<T>(LinkedList<T>& previous);
    LinkedList<T>(T nodeData);
    LinkedList<T>(T nodeData, LinkedList<T>& previous);
    LinkedList<T>(LinkedList<T>& previous, T nodeData);

    LinkedList<T>* end();
    LinkedList<T>& operator[](int i);
    LinkedList<T> push(LinkedList node);
    LinkedList<T> push(T nodeData);

//    ~LinkedList<T>();
};

template class LinkedList<string>;
template class LinkedList<int>;
template class LinkedList<double>;

#endif //CPPREF_LINKEDLIST_H
