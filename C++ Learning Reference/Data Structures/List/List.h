#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include <string>

template <typename T>
class List {
public:
    T item;
    List<T>* next;

    List<T>(const List<T>& other);

    List<T>();
    List<T>(List<T>& previous);
    List<T>(T item);
    List<T>(T item, List<T>& previous);
    List<T>(List<T>& previous, T item);

    List<T>* end();
    List<T>& operator[](int i);
    List<T>* push(List<T>& node);
    List<T>* push(T item);

    List<T> pop();
    List<T> pop(int at);
    List<T> shift();
    List<T> unshift(List<T>& node);
    List<T> unshift(T item);

    List<T> excise(int from, int to);
    List<T> splice(int at, List<T>& node);
    List<T> splice(int at, T item);
    List<T>& slice(int index);

    std::string toString();
    int print();

    ~List<T>();
};

template class List<std::string>;
template class List<int>;
template class List<double>;

#endif //CPPREF_LINKEDLIST_H
