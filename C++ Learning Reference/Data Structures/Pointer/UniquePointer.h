#ifndef CPPREF_UNIQUE_H
#define CPPREF_UNIQUE_H

// for std
#include <string>
using std::nullptr_t;

namespace Lehr {

    template<typename T>
    class UniquePointer {
    public:
        UniquePointer();
//        UniquePointer(T& pointee);
        UniquePointer(T* pointer);
        UniquePointer(UniquePointer<T>& other);
        UniquePointer(UniquePointer<T>&& other);
        void operator =(UniquePointer<T>& other);
        void operator =(UniquePointer<T>&& other);
        void operator =(T& item);
        void operator =(T&& item);
        ~UniquePointer();

        bool operator ==(nullptr_t nil);
        bool operator !=(nullptr_t nil);
        bool operator ==(T* ptr);
        bool operator !=(T* ptr);
        bool operator ==(UniquePointer<T> u_ptr);
        bool operator !=(UniquePointer<T> u_ptr);

        // would explicit cast to raw ptr be a dangerous method to have?
        T* get();
        T& operator *();
        T* operator ->();
    protected:
        void take_over(UniquePointer<T>& other);
        void free();
        void release();
    private:
        T* raw_pointer = nullptr;
    };

}

namespace Lehr {

    template<typename T>
    UniquePointer<T>::UniquePointer() {}
//    template<typename T>
//    UniquePointer<T>::UniquePointer(T& pointee) {
//        raw_pointer = &pointee;
//    }
    template<typename T>
    UniquePointer<T>::UniquePointer(T* pointer) {
        free();
        raw_pointer = pointer;
    };
    template<typename T>
    UniquePointer<T>::UniquePointer(UniquePointer<T>& other) {
        take_over(other);
    };
    template<typename T>
    UniquePointer<T>::UniquePointer(UniquePointer<T>&& other) {
        take_over(other);
    };
    template<typename T>
    void UniquePointer<T>::operator =(UniquePointer<T>& other) {
        take_over(other);
    };
    template<typename T>
    void UniquePointer<T>::operator =(UniquePointer<T>&& other) {
        take_over(other);
    };

    template<typename T>
    void UniquePointer<T>::operator =(T& item) {
        raw_pointer = &item;
    };
    template<typename T>
    void UniquePointer<T>::operator =(T&& item) {
        raw_pointer = &item;
    };

    template<typename T>
    UniquePointer<T>::~UniquePointer() {
        free();
    };
    template<typename T>
    bool UniquePointer<T>::operator ==(nullptr_t nil) {
        return raw_pointer == nil;
    }
    template<typename T>
    bool UniquePointer<T>::operator !=(nullptr_t nil) {
        return !operator ==(nil);
    }
    template<typename T>
    bool UniquePointer<T>::operator ==(T* ptr) {
        return raw_pointer == ptr;
    }
    template<typename T>
    bool UniquePointer<T>::operator !=(T* ptr) {
        return !operator ==(ptr);
    }
    template<typename T>
    bool UniquePointer<T>::operator ==(UniquePointer<T> u_ptr) {
        return false;
    }
    template<typename T>
    bool UniquePointer<T>::operator !=(UniquePointer<T> u_ptr) {
        return true;
    }
    template<typename T>
    T* UniquePointer<T>::get() {
        return raw_pointer;
    }
    template<typename T>
    T& UniquePointer<T>::operator *() {
        return *raw_pointer;
    };
    template<typename T>
    T* UniquePointer<T>::operator ->() {
        return raw_pointer;
    };
    template<typename T>
    void UniquePointer<T>::take_over(UniquePointer<T>& other) {
        raw_pointer = other.raw_pointer;
        other.release();
    }
    template<typename T>
    void UniquePointer<T>::free() {
        if (raw_pointer != nullptr) {
            delete raw_pointer;
            raw_pointer = nullptr;
        }
    }
    template<typename T>
    void UniquePointer<T>::release() {
        raw_pointer = nullptr;
    }

}


#endif //CPPREF_UNIQUE_H
