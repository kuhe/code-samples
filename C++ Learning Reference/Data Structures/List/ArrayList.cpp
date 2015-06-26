//
#include "ArrayList.h"

namespace Lehr {
    template <typename T>
    void ArrayList<T>::resize(int n) {
        if (data != nullptr) {
            delete[] data;
        }
        data = new T[n];
        length = 0;
    }
    template <typename T>
    void ArrayList<T>::copyFrom(T* source, int length) {
        for (int i = 0; i < sizeof source; i++) {
            data[length - 1] = *(source + 1);
            length++;
        }
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
        copyFrom(source.data, source.length);
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
//        if (sizeof data >= length) {
//            T store = *data;
//            resize((int) (RESIZE_SCALAR * length));
//            copyFrom(store, length);
//        }
//        data[length] = item;
//        length++;
        return this;
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::unshift(T item) {
//        T store = *data;
//        int original_length = length;
//        if (sizeof data >= length) {
//            resize((int) (RESIZE_SCALAR * length));
//        } else {
//            resize(length);
//        }
//        data[0] = item;
//        length++;
//        copyFrom(store, original_length);
        return this;
    }

    template <typename T>
    T ArrayList<T>::pop() {
        T x;
        return x;
    }
    template <typename T>
    T ArrayList<T>::shift() {
        T x;
        return x;
    }
    template <typename T>
    ArrayList<T> ArrayList<T>::excise(int at) {
        return *this;
    }
    template <typename T>
    ArrayList<T> ArrayList<T>::excise(int from, int to) {
        return *this;
    }
    template <typename T>
    ArrayList<T> ArrayList<T>::splice(int before, ArrayList<T>& list) {
        return *this;
    }
    template <typename T>
    ArrayList<T> ArrayList<T>::splice(int before, T& item) {
        return *this;
    }
    template <typename T>
    ArrayList<T> ArrayList<T>::slice(int index) {
        while (index--) {
            shift();
        }
        return *this;
    }
    template <typename T>
    ArrayList<T> ArrayList<T>::slice(int index, int length) {
        while (index--) {
            shift();
        }
        while (this->length > length) {
            pop();
        }
        return *this;
    }
}
