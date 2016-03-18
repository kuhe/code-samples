#ifndef CPPREF_LISTINTERFACE_H
#define CPPREF_LISTINTERFACE_H

#include "_list_common.h"
class ListInterface;

namespace Lehr {
    template <typename T>
    class List {
    public:
        virtual int count() = 0;
//        List<T>();
//        List<T>(T item);
//        List<T>(const List<T>& copy);
        virtual ~List<T>() {};

        virtual T& operator[](int i) = 0;

        virtual List<T>* push(T item) = 0;
        virtual List<T>* unshift(T item) = 0;

        virtual T* pop() = 0;
        virtual T* shift() = 0;

        virtual int index(const T& item) = 0;
        virtual bool contains(const T& item) = 0;

        virtual List<T>* sort() = 0;
    };
}

#endif //CPPREF_LISTINTERFACE_H
