#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include "ListInterface.h"
#include <string>

namespace Lehr {
    template <typename T>
    class List : public ListInterface<T> {
    protected:
        int length = 0;
        struct Node {
            friend class List<T>;
            T item;
            Node* next = nullptr;
            Node() {};
            Node(T item) : item(item) {};
            Node(Node* next) : next(next) {};
            Node(T item, Node* next) : item(item), next(next) {};
            Node(Node* next, T item) : item(item), next(next) {};
            void operator =(T item) {
                this->item = item;
            };
        };
        Node* head = nullptr;
        Node* tail = nullptr;
        Node* nodeAt(int i);
    public:
        int count();

        List<T>();
        List<T>(T item);
        List<T>(const List<T>& copy);
        ~List<T>();

        T& operator[](int i);

        List<T>* push(T item);
        List<T>* unshift(T item);

        T pop();
        T shift();

        /**
         * mutation methods
         */
        List<T>& excise(int at);
        List<T>& excise(int from, int to);
        List<T>& splice(int before, List<T>& list);
        List<T>& splice(int before, T& item);
        List<T>& slice(int index);
        List<T>& slice(int index, int length);
    };

    template class List<std::string>;
    template class List<int>;
    template class List<double>;
}

namespace Lehr {
    template <typename T>
    int List<T>::count() {
        return length;
    }
    template <typename T>
    List<T>::List() {
    }
    template <typename T>
    List<T>::List(T item) {
        length = 1;
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
        Node* cursor = head;
        while (nullptr != cursor) {
            Node* deletion = cursor;
            cursor = cursor->next;
            delete deletion;
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
    List<T>& List<T>::excise(int at) {
        if (at > 1) {
            nodeAt(at - 1)->next = nodeAt(at + 1);
            length--;
        } else {
            shift();
        }
        return *this;
    }
    template <typename T>
    List<T>& List<T>::excise(int from, int to) {
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
    List<T>& List<T>::splice(int before, List<T>& list) {
        length += list.length;
        if (before > 0) {
            Node* diverge_at = nodeAt(before - 1);
            Node* rejoin_at = nodeAt(before);
            Node* cursor = diverge_at;
            while (list.length) {
                Node* node_copy = new Node(list.shift());
                cursor->next = node_copy;
                cursor = node_copy;
            }
            cursor->next = rejoin_at;
        } else {
            list.tail->next = head;
            head = list.head;
        }
        List<T>& examine = *this;
        return *this;
    }
    template <typename T>
    List<T>& List<T>::splice(int before, T& item) {
        List<T> container(item);
        return splice(before, container);
    }
    template <typename T>
    List<T>& List<T>::slice(int index) {
        while (index--) {
            shift();
        }
        return *this;
    }
    template <typename T>
    List<T>& List<T>::slice(int index, int length) {
        while (index--) {
            shift();
        }
        while (this->length > length) {
            pop();
        }
        return *this;
    }
}

#endif //CPPREF_LINKEDLIST_H

