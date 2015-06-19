#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include <string>

template <typename T>
class List {
private:
    struct Node {
        T item;
        Node* next;
    };
protected:
    int length;
public:
    Node* head;
    Node* tail;
    int count();

    List<T>();
    List<T>(T item);
    List<T>(const List<T>& copy);
    ~List<T>();

    List<T>& operator[](int i);

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
