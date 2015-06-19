//
#include "_list_common.h"
#include "List.h"

namespace Lehr_DS {
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
        if (i > 0) {
            cursor = nullptr;
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
            List<T>::Node* new_tail = nodeAt(length - 2);
            new_tail->next = nullptr;
            tail = new_tail;
        }
        length--;
        return data;
    }
    template <typename T>
    T List<T>::shift() {
        T data = head->item;
        Node* current_head = head;
        head = nullptr;
        if (length > 1) {
            head = current_head->next;
        }
        delete current_head;
        length--;
        return data;
    }
    template <typename T>
    List<T> List<T>::excise(int at) {
        if (at > 1) {
            nodeAt(at - 1)->next = nodeAt(at + 1);
            length--;
        } else {
            shift();
        }
        return *this;
    }
    template <typename T>
    List<T> List<T>::excise(int from, int to) {
        if (from > 1) {
            nodeAt(from - 1)->next = nodeAt(to + 1);
            length -= to - from + 1;
        } else {
            int n = 0;
            while (n++ <= to) {
                shift();
            }
        }
        return *this;
    }
    template <typename T>
    List<T> List<T>::splice(int before, List<T>& list) {
        length += list.length;
        if (before > 0) {
            nodeAt(before - 1)->next = list.head;
            if (before >= length) {
                tail = list.tail;
            } else {
                list.tail->next = nodeAt(before);
            }
        } else {
            list.tail->next = head;
            head = list.head;
        }
        return *this;
    }
    template <typename T>
    List<T> List<T>::splice(int before, T& item) {
        if (before > 0) {
            Node* node = new Node(item);
            nodeAt(before - 1)->next = node;
            if (before >= length) {
                push(item);
            } else {
                length++;
                node->next = nodeAt(before);
            }
        } else {
            unshift(item);
        }
        return *this;
    }
    template <typename T>
    List<T> List<T>::slice(int index) {
        while (index--) {
            shift();
        }
        return *this;
    }
    template <typename T>
    List<T> List<T>::slice(int index, int length) {
        while (index--) {
            shift();
        }
        while (this->length > length) {
            pop();
        }
        return *this;
    }
}
