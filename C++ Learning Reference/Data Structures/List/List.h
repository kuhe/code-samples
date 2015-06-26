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
        List<T> excise(int at);
        List<T> excise(int from, int to);
        List<T> splice(int before, List<T>& list);
        List<T> splice(int before, T& item);
        List<T> slice(int index);
        List<T> slice(int index, int length);
    };

    template class List<std::string>;
    template class List<int>;
    template class List<double>;
}

#endif //CPPREF_LINKEDLIST_H
