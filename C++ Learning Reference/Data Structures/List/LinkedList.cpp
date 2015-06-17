//
#include <c++/ostream>
#include <c++/iostream>
#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList() {
    next = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>& previous) {
    previous.next = this;
    next = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(T nodeData) {
    next = nullptr;
    data = nodeData;
}

template <typename T>
LinkedList<T>::LinkedList(T nodeData, LinkedList<T>& previous) {
    previous.next = this;
    data = nodeData;
    next = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>& previous, T nodeData) {
    data = nodeData;
    previous.next = this;
    next = nullptr;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator [](int i) {
    LinkedList<T>* list_ptr = this;
    double n = (double) i;
    while (n > 0) {
        list_ptr = (*list_ptr).next;
        n--;
    }
    return *list_ptr;
}

template <typename T>
LinkedList<T>* LinkedList<T>::end() {
    LinkedList<T>* list_ptr = this;
    while (nullptr != (*list_ptr).next) {
        list_ptr = (*list_ptr).next;
    }
    return list_ptr;
}

template <typename T>
LinkedList<T> LinkedList<T>::push(LinkedList node) {
    LinkedList<T>* end_ptr = end();
    LinkedList<T>* node_ptr = &node;
    (*end_ptr).next = node_ptr;
    return node;
}

template <typename T>
LinkedList<T> LinkedList<T>::push(T nodeData) {
    LinkedList<T>* node_ptr = new LinkedList<T>(*(end()), nodeData);
    return *node_ptr;
}

//template <typename T>
//LinkedList<T>::~LinkedList() {
//    delete this->next;
//}