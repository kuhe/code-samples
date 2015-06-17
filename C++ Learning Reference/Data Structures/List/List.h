#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include <string>

template <typename T>
class List {
public:
    T data;
    List<T>* next;
    List<T>();
    List<T>(List<T>& previous);
    List<T>(T nodeData);
    List<T>(T nodeData, List<T>& previous);
    List<T>(List<T>& previous, T nodeData);

    List<T>* end();
    List<T>& operator[](int i);
    List<T>* push(List<T>& node);
    List<T>* push(T nodeData);

    List<T> pop();
    List<T> pop(int at);
    List<T> shift();
    List<T> unshift(List<T>& node);
    List<T> unshift(T nodeData);

    List<T> excise(int from, int to);
    List<T> slice(int index);

    std::string toString();
    int print();

    ~List<T>();
};

template class List<std::string>;
template class List<int>;
template class List<double>;

#endif //CPPREF_LINKEDLIST_H
