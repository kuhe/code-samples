//
#include "_list_common.h"
#include "List.h"

template <typename T>
int List<T>::count() {
    return length;
}
template <typename T>
List<T>::List() {
}
template <typename T>
List<T>::List(T item) {
    head = new List<T>::Node(item);
    tail = head;
}
template <typename T>
List<T>::List(const List<T>& source) {
    List<T>::Node* cursor = source.head;
    while (nullptr != cursor) {
        this->push(cursor->item);
        cursor = cursor->next;
    }
}
template <typename T>
List<T>::~List() {
    while (length) {
        shift();
    }
}

template <typename T>
T& List<T>::operator[](int i) {
    List<T>::Node* cursor = this->head;
    while (nullptr != cursor->next && i--) {
        cursor = cursor->next;
    }
    return cursor->item;
}

template <typename T>
typename List<T>::Node* List<T>::nodeAt(int i) {
    List<T>::Node* cursor = this->head;
    while (nullptr != cursor->next && i--) {
        cursor = cursor->next;
    }
    return cursor;
}

template <typename T>
List<T>* List<T>::push(T item) {
    List<T>::Node* node = new List<T>::Node(item);
    if (nullptr != tail) {
        tail->next = node;
    } else {
        head = node;
    }
    tail = node;
    length++;
    return this;
}
template <typename T>
List<T>* List<T>::unshift(T item) {
    List<T>::Node* node = new List<T>::Node(item);
    if (nullptr != head) {
        node->next = head;
    } else {
        tail = node;
    }
    head = node;
    length++;
    return this;
}

template <typename T>
T List<T>::pop() {
    T data = tail->item;
    delete tail;
    if (length > 1) {
        List<T>::Node* newTail = nodeAt(length - 2);
        newTail->next = nullptr;
        tail = newTail;
    }
    length--;
    return data;
}
template <typename T>
T List<T>::shift() {
    T data = head->item;
    Node* currentHead = head;
    head = nullptr;
    if (length > 1) {
        head = currentHead->next;
    }
    delete currentHead;
    length--;
    return data;
}
template <typename T>
List<T> List<T>::excise(int at) {
    return *this;
}
template <typename T>
List<T> List<T>::excise(int from, int to) {
    return *this;
}
template <typename T>
List<T> List<T>::splice(int at, List<T>& node) {
    return *this;
}
template <typename T>
List<T> List<T>::splice(int at, T& item) {
    return *this;
}
template <typename T>
List<T> List<T>::slice(int index) {
    return *this;
}
template <typename T>
List<T> List<T>::slice(int index, int length) {
    return *this;
}