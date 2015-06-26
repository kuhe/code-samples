
#ifndef CPPREF_LISTINTERFACE_H
#define CPPREF_LISTINTERFACE_H

#include "_list_common.h"
class ListInterface;

namespace Lehr {
    template <typename T>
    class ListInterface {
    public:
        virtual int count() = 0;
//        ListInterface<T>();
//        ListInterface<T>(T item);
//        ListInterface<T>(const ListInterface<T>& copy);
        virtual ~ListInterface<T>() {};

        virtual T& operator[](int i) = 0;

        virtual ListInterface<T>* push(T item) = 0;
        virtual ListInterface<T>* unshift(T item) = 0;

        virtual T pop() = 0;
        virtual T shift() = 0;
    };
}

#endif //CPPREF_LISTINTERFACE_H
