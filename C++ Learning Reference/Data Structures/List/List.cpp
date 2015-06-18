//
#include <c++/ostream>
#include <iostream>
#include "List.h"

template <typename T>
List<T>::List() {
    next = nullptr;
}

template <typename T>
List<T>::List(List<T>& previous) {
    previous.next = this;
    next = nullptr;
}

template <typename T>
List<T>::List(T item) {
    next = nullptr;
    this->item = item;
}

template <typename T>
List<T>::List(T item, List<T>& previous) {
    previous.next = this;
    this->item = item;
    next = nullptr;
}

template <typename T>
List<T>::List(List<T>& previous, T item) {
    this->item = item;
    previous.next = this;
    next = nullptr;
}

template <typename T>
List<T>& List<T>::operator [](int i) {
    List<T>* list_ptr = this;
    double n = (double) i;
    while (n > 0) {
        list_ptr = (*list_ptr).next;
        n--;
    }
    return *list_ptr;
}

template <typename T>
List<T>* List<T>::end() {
    List<T>* list_ptr = &*this;
    while (nullptr != (*list_ptr).next) {
        list_ptr = (*list_ptr).next;
    }
    return list_ptr;
}

template <typename T>
List<T>* List<T>::push(List<T>& node) {
    List<T>* node_ptr = &node;
    List<T>& previousNode = *end();
    previousNode.next = node_ptr;
    return node_ptr;
}

template <typename T>
List<T>* List<T>::push(T item) {
    List<T>& previousNode = *end();
    return new List<T>(item, previousNode);
}

template <typename T>
List<T>::~List() {
//    delete this->next;
}

template <typename T>
List<T> List<T>::pop() {
    List<T>* list_ptr = this;
    List<T>* prev_ptr = nullptr;
    while (nullptr != (*list_ptr).next) {
        prev_ptr = list_ptr;
        list_ptr = (*list_ptr).next;
    }
    if (nullptr != prev_ptr) {
        (*prev_ptr).next = nullptr;
    }
    return *list_ptr;
}
template <typename T>
List<T> List<T>::pop(int at) {
    List<T> node = (*this)[at];
    excise(at, at + 2);
    return node;
}
template <typename T>
List<T> List<T>::shift() {
    List<T>& head = *this;
    (*this) = *(head.next);
    head.next = nullptr;
    return head;
}
template <typename T>
List<T> List<T>::unshift(List<T>& node){
    node.next = this;
    return node;
}
template <typename T>
List<T> List<T>::unshift(T item){
    List<T>* node_ptr = new List<T>(item);
    (*node_ptr).next = this;
    return *node_ptr;
}
template <typename T>
List<T> List<T>::excise(int from, int to){
    if (to > from) {
        (*this)[from].next = &(*this)[to];
    }
    return *this;
}

template <typename T>
List<T> List<T>::splice(int at, List<T>& list) {
    List<T>& nodeAt = (*this)[at];
    (*(list.end())).next = nodeAt.next;
    nodeAt.next = &list;
    return *this;
}

template <typename T>
List<T> List<T>::splice(int at, T item) {
    List<T>& nodeAt = (*this)[at];
    List<T>* newNode_ptr = new List<T>(item);
    (*newNode_ptr).next = nodeAt.next;
    nodeAt.next = newNode_ptr;
    return *this;
}

template <typename T>
List<T>& List<T>::slice(int index){
    List<T>& test = (*this)[index];
    return test;
}

template <typename T>
std::string List<T>::toString() {
    std::string output = "";
    List<T>* list_ptr = this;
    output += (*list_ptr).item;
    while (nullptr != (*list_ptr).next) {
        list_ptr = (*list_ptr).next;
        output += (*list_ptr).item;
    }
    return output;
}

template <typename T>
int List<T>::print() {
    std::cout << toString() << std::endl;
    return 0;
}