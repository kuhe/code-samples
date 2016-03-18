#ifndef CPPREF_ARRAYLIST_H
#define CPPREF_ARRAYLIST_H

#include "List.h"
#include <string>
#include <array>

using std::array;

namespace Lehr {
    template <typename T>
    class ArrayList : public List<T> {
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

        int index(T& item);
        bool contains(T& item);

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

namespace Lehr {
    template <typename T>
    void ArrayList<T>::resize(int n, int start_index) {
        T* transfer;
        transfer = new T[n];
        for (int i = 0; i + start_index < length && i < n; i++) {
            transfer[i] = data[i + start_index];
        }
        if (data != nullptr) {
            delete[] data;
        }
        length -= start_index;
        data = transfer;
    }

    template <typename T>
    int ArrayList<T>::count() {
        return length;
    }
    template <typename T>
    ArrayList<T>::ArrayList() {
        resize(0);
    }
    template <typename T>
    ArrayList<T>::ArrayList(T item) {
        resize(1);
        data[0] = item;
        length = 1;
    }
    template <typename T>
    ArrayList<T>::ArrayList(const ArrayList<T>& source) {
        resize(source.length);
        length = source.length;
        for (int i = 0; i < length; i++) {
            data[i] = *(source.data + i);
        }
    }
    template <typename T>
    ArrayList<T>::~ArrayList() {
        delete[] data;
    }

    template <typename T>
    T& ArrayList<T>::operator[](int i) {
        return data[i];
    }

    template <typename T>
    ArrayList<T>* ArrayList<T>::push(T item) {
        if (sizeof data >= length) {
            resize((int) (RESIZE_SCALAR * (length + 1)));
        }
        data[length] = item;
        length++;
        return this;
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::unshift(T item) {
        if (sizeof data >= length + 1) {
            resize((int) (RESIZE_SCALAR * (length + 2)));
        }
        for (int i = length; i > 0; i--) {
            data[i] = data[i-1];
        }
        data[0] = item;
        length++;
        return this;
    }

    template <typename T>
    T ArrayList<T>::pop() {
        if (length > 0) {
            int index = length - 1;
            T value = data[index];
            length--;
            return value;
        }
        T dummy;
        return dummy;
    }
    template <typename T>
    T ArrayList<T>::shift() {
        if (length > 0) {
            T value = data[0];
            resize(sizeof data, 1);
            return value;
        }
        T dummy;
        return dummy;
    }
    template <typename T>
    int ArrayList<T>::index(T& item) {
        int index = 0;
        T& cursor = this->operator[](index);
        while (index < length) {
            if (this->operator[](index) == item) {
                return index;
            }
            index++;
            cursor = this->operator[](index);
        }
        return -1;
    }
    template <typename T>
    bool ArrayList<T>::contains(T& item) {
        return index(item) > -1;
    }
    template <typename T>
    ArrayList<T>& ArrayList<T>::excise(int at) {
        return excise(at, at);
    }
    template <typename T>
    ArrayList<T>& ArrayList<T>::excise(int from, int to) {
        if (to < from) return *this;
        T empty;
        int offset = to - from + 1;
        for (int i = from; i <= to; i++) {
            data[i] = data[i + offset];
            data[i + offset] = empty;
        }
        length -= 1 + (to - from);
        return *this;
    }
    template <typename T>
    ArrayList<T>& ArrayList<T>::splice(int before, ArrayList<T>& list) {
        if (before >= length) {
            for (int i = 0; i < list.length; i++) {
                push(list[i]);
            }
        } else {
            resize(length + list.length);

            // hello how name is
            // hello how __ __ __ name is
            // ^ are you my

            for (int i = before; i <= length; i++) {
                data[i + list.length] = data[i];
            }
            for (int j = before; j < before + list.length; j++) {
                data[j] = list[j - before];
            }
            length += list.length;
        }
        return *this;
    }
    template <typename T>
    ArrayList<T>& ArrayList<T>::splice(int before, T& item) {
        ArrayList<T> container(item);
        return splice(before, container);
    }
    template <typename T>
    ArrayList<T>& ArrayList<T>::slice(int index) {
        while (index--) {
            shift();
        }
        return *this;
    }
    template <typename T>
    ArrayList<T>& ArrayList<T>::slice(int index, int length) {
        while (index--) {
            shift();
        }
        while (this->length > length) {
            pop();
        }
        return *this;
    }
}


#endif //CPPREF_ARRAYLIST_H

