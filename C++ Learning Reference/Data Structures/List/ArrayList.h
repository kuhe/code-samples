#ifndef CPPREF_ARRAYLIST_H
#define CPPREF_ARRAYLIST_H

#include "ListInterface.h"
#include "../Map/Map.h"
#include <string>
#include <array>

using std::array;

namespace Lehr {
    template <typename T>
    class ArrayList : public ListInterface<T> {
    protected:
        const double RESIZE_SCALAR = 1.5;
        int length = 0;
        T* data = nullptr;
        void resize(int n, int start_index = 0);
    public:
        int count();

        ArrayList<T>();
        ArrayList<T>(T item);
        ArrayList<T>(const ArrayList<T>& copy);
        ~ArrayList<T>();

        T& operator[](int i);

        ArrayList<T>* push(T item);
        ArrayList<T>* unshift(T item);

        T pop();
        T shift();

        /**
         * mutation methods
         */
        ArrayList<T>& excise(int at);
        ArrayList<T>& excise(int from, int to);
        ArrayList<T>& splice(int before, ArrayList<T>& list);
        ArrayList<T>& splice(int before, T& item);
        ArrayList<T>& slice(int index);
        ArrayList<T>& slice(int index, int length);
    };

    template class ArrayList<std::string>;
    template class ArrayList<int>;
    template class ArrayList<double>;
}

#endif //CPPREF_ARRAYLIST_H
