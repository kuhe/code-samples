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
List<T>::List(T nodeData) {
    next = nullptr;
    data = nodeData;
}

template <typename T>
List<T>::List(T nodeData, List<T>& previous) {
    previous.next = this;
    data = nodeData;
    next = nullptr;
}

template <typename T>
List<T>::List(List<T>& previous, T nodeData) {
    data = nodeData;
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
    List<T>* list_ptr = this;
    while (nullptr != (*list_ptr).next) {
        list_ptr = (*list_ptr).next;
    }
    return list_ptr;
}

template <typename T>
List<T> List<T>::push(List<T>& node) {
    List<T>* node_ptr = &node;
    (*end()).next = node_ptr;
    return node;
}

template <typename T>
List<T>* List<T>::push(T nodeData) {
    return new List<T>(nodeData, *end());
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
    List<T> head = *this;
    head.next = nullptr;
    return head;
}
template <typename T>
List<T> List<T>::unshift(List<T>& node){
    node.next = this;
    return node;
}
template <typename T>
List<T> List<T>::unshift(T nodeData){
    List<T>* node_ptr = new List<T>(nodeData);
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
List<T> List<T>::slice(int index){
    return (*this)[index];
}

template <typename T>
std::string List<T>::toString() {
    std::string output = "";
    List<T>* list_ptr = this;
    output += (*list_ptr).data;
    while (nullptr != (*list_ptr).next) {
        list_ptr = (*list_ptr).next;
        output += (*list_ptr).data;
    }
    return output;
}

template <typename T>
int List<T>::print() {
    std::cout << toString() << std::endl;
    return 0;
}