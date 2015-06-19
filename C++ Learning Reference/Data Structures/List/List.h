#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include <string>

template <typename T>
class List {
protected:
    int length = 0;
public:
    struct Node {
    friend class List<T>;
        T item;
        Node* next;
        Node() {};
        Node(T item) : item(item) {};
        Node(Node* next) : next(next) {};
        Node(T item, Node* next) : item(item), next(next) {};
        Node(Node* next, T item) : item(item), next(next) {};
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int count();

    List<T>();
    List<T>(T item);
    List<T>(const List<T>& copy);
    ~List<T>();

    T& operator[](int i);
    Node* nodeAt(int i);

    List<T>* push(T item);
    List<T>* unshift(T item);

    T pop();
    T shift();

    List<T> excise(int at);
    List<T> excise(int from, int to);
    List<T> splice(int at, List<T>& node);
    List<T> splice(int at, T& item);
    List<T> slice(int index);
    List<T> slice(int index, int length);
};

template class List<std::string>;
template class List<int>;
template class List<double>;

#endif //CPPREF_LINKEDLIST_H
