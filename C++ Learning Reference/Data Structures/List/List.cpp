//
#include "_list_common.h"
#include "List.h"

template <typename T>
List<T>::List() {
    next = nullptr;
}
template <typename T>
List<T>::List(T item) : item(item) {
    next = nullptr;
};
template <typename T>
List<T>* List<T>::end() {
    List<T>* cursor = this;
    while (cursor->next != nullptr) {
        cursor = cursor->next;
    }
    return cursor;
}
template <typename T>
List<T>& List<T>::operator[](int i) {
    List<T>* cursor = this;
    while ((*cursor).next != nullptr && i--) {
        cursor = (*cursor).next;
    }
    return *cursor;
}
template <typename T>
List<T>* List<T>::push(T item) {
    end()->next = new List<T>(item);
    return this;
}
template <typename T>
List<T>* List<T>::unshift(T item) {
    List<T> copy = *this;
    this->item = item;
    next = new List<T>(copy.item);
    next->next = copy.next;
    return this;
}
template <typename T>
T List<T>::pop() {
    List<T>* cursor = this;
    List<T>* last = nullptr;
    while ((*cursor).next != nullptr) {
        last = cursor;
        cursor = (*cursor).next;
    }
    if (nullptr != last) {
        last->next = nullptr;
    }
    T copy = cursor->item;
    delete cursor;
    return copy;
}
template <typename T>
T List<T>::pop(int at) {
    List<T>* cursor = this;
    List<T>* last = nullptr;
    while (at-- && (*cursor).next != nullptr) {
        last = cursor;
        cursor = (*cursor).next;
    }
    if (nullptr != last) {
        last->next = nullptr;
    }
    T copy = cursor->item;
    delete cursor;
    return copy;
}
//template <typename T>
//T List<T>::shift() {
//}
//template <typename T>
//List<T> List<T>::excise(int from, int to) {
//
//}
//template <typename T>
//List<T> List<T>::splice(int at, List<T>& node) {
//
//}
//template <typename T>
//List<T> List<T>::splice(int at, T& item) {
//
//}
//template <typename T>
//List<T>& List<T>::slice(int index) {
//
//}
//template <typename T>
//List<T>::~List<T>() {
//
//}