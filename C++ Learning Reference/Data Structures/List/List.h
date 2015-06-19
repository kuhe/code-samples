#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include <string>

template <typename T>
class List {
public:
    T item;
    List<T>* next;

    List<T>();
    List<T>(T item);

    List<T>* end();
    List<T>& operator[](int i);

    List<T>* push(T item);
    List<T>* unshift(T item);

    T pop();
    T pop(int at);
//    T shift();

//    List<T> excise(int from, int to);
//    List<T> splice(int at, List<T>& node);
//    List<T> splice(int at, T& item);
//    List<T>& slice(int index);
//
//protected:
//    ~List<T>();
};

template class List<std::string>;
template class List<int>;
template class List<double>;

#endif //CPPREF_LINKEDLIST_H
