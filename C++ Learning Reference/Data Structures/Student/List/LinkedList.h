#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include "List.h"
#include <string>

namespace Lehr {
    template <typename T>
    class LinkedList : public List<T> {
    public:
        int count();

        LinkedList<T>();
        LinkedList<T>(T item);
        LinkedList<T>(const LinkedList<T>& copy);
        ~LinkedList<T>();

        T& operator[](int i);

        LinkedList<T>* push(T item);
        LinkedList<T>* unshift(T item);

        T* pop();
        T* shift();

        int index(const T& item);
        bool contains(const T& item);

        /**
         * mutation methods
         */
        LinkedList<T>* sort();
        LinkedList<T>* excise(int at);
        LinkedList<T>* excise(int from, int to);
        LinkedList<T>* splice(int before, LinkedList<T>& list);
        LinkedList<T>* splice(int before, T& item);
        LinkedList<T>* slice(int index);
        LinkedList<T>* slice(int index, int length);
    protected:
        int length = 0;
        struct Node {
            friend class LinkedList<T>;
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
    };

    template class LinkedList<std::string>;
    template class LinkedList<int>;
    template class LinkedList<double>;
}

namespace Lehr {
    template <typename T>
    int LinkedList<T>::count() {
        return length;
    }
    template <typename T>
    LinkedList<T>::LinkedList() {
    }
    template <typename T>
    LinkedList<T>::LinkedList(T item) {
        length = 1;
        head = new LinkedList<T>::Node(item);
        tail = head;
    }
    template <typename T>
    LinkedList<T>::LinkedList(const LinkedList<T>& source) {
        LinkedList<T>::Node* cursor = source.head;
        while (nullptr != cursor) {
            push(cursor->item);
            cursor = cursor->next;
        }
    }
    template <typename T>
    LinkedList<T>::~LinkedList() {
        Node* cursor = head;
        while (nullptr != cursor) {
            Node* deletion = cursor;
            cursor = cursor->next;
            delete deletion;
        }
    }

    template <typename T>
    T& LinkedList<T>::operator[](int i) {
        LinkedList<T>::Node* cursor = this->head;
        while ((nullptr != cursor->next) && (i > 0)) {
            cursor = cursor->next;
            i--;
        }
        return cursor->item;
    }

    template <typename T>
    typename LinkedList<T>::Node* LinkedList<T>::nodeAt(int i) {
        LinkedList<T>::Node* cursor = this->head;
        while (nullptr != cursor->next && i--) {
            cursor = cursor->next;
        }
        if (i > 0) {
            cursor = nullptr;
        }
        return cursor;
    }

    template <typename T>
    LinkedList<T>* LinkedList<T>::push(T item) {
        T copy = item;
        LinkedList<T>::Node* node = new LinkedList<T>::Node(copy);
        if (nullptr != tail) {
            tail->next = node;
            tail = tail->next;
        } else {
            head = node;
            tail = node;
        }
        length++;
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::unshift(T item) {
        LinkedList<T>::Node* node = new LinkedList<T>::Node(item);
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
    T* LinkedList<T>::pop() {
        T& data = tail->item;
        delete tail;
        if (length > 1) {
            LinkedList<T>::Node* new_tail = nodeAt(length - 2);
            new_tail->next = nullptr;
            tail = new_tail;
        }
        length--;
        return &data;
    }
    template <typename T>
    T* LinkedList<T>::shift() {
        T& data = head->item;
        Node* current_head = head;
        head = nullptr;
        if (length > 1) {
            head = current_head->next;
        }
        delete current_head;
        length--;
        return &data;
    }
    template <typename T>
    int LinkedList<T>::index(const T& item) {
        Node* cursor = head;
        int index = 0;
        while (nullptr != cursor) {
            if (cursor->item == item) {
                return index;
            }
            index++;
            cursor = cursor->next;
        }
        return -1;
    }
    template <typename T>
    bool LinkedList<T>::contains(const T& item) {
        return index(item) > -1;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::sort() {
        // todo
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::excise(int at) {
        if (at > 1) {
            nodeAt(at - 1)->next = nodeAt(at + 1);
            length--;
        } else {
            shift();
        }
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::excise(int from, int to) {
        if (from > 1) {
            nodeAt(from - 1)->next = nodeAt(to + 1);
            length -= to - from + 1;
        } else {
            int n = 0;
            while (n++ <= to) {
                shift();
            }
        }
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::splice(int before, LinkedList<T>& list) {
        int original_length = length;
        length += list.length;
        if (before > 0) {
            Node* diverge_at = nodeAt(before - 1);
            Node* rejoin_at = nodeAt(before);
            Node* cursor = diverge_at;
            while (list.length) {
                Node* node_copy = new Node(*list.shift());
                cursor->next = node_copy;
                cursor = cursor->next;
            }
            cursor->next = rejoin_at;
            if (before >= original_length) {
                tail = cursor;
            }
        } else {
            list.tail->next = head;
            head = list.head;
        }
        LinkedList<T>& examine = *this;
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::splice(int before, T& item) {
        LinkedList<T> container(item);
        return splice(before, container);
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::slice(int index) {
        while (index--) {
            shift();
        }
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::slice(int index, int length) {
        while (index--) {
            shift();
        }
        while (this->length > length) {
            pop();
        }
        return this;
    }
}

#endif //CPPREF_LINKEDLIST_H

