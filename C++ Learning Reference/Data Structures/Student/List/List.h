#ifndef CPPREF_LISTINTERFACE_H
#define CPPREF_LISTINTERFACE_H

#include "_list_common.h"

namespace Lehr {
    template <typename T>
    class List {
    public:
        virtual int size() = 0;
//        List<T>();
//        List<T>(T item);
//        List<T>(const List<T>& copy);
        virtual ~List<T>() {};

        virtual T& operator[](int i) = 0;

        virtual List<T>* push(T item) = 0;
        virtual List<T>* unshift(T item) = 0;

        virtual void pop() = 0;
        virtual void shift() = 0;
        virtual void pop(T& into) = 0;
        virtual void shift(T& into) = 0;
        virtual T& begin() = 0;
        virtual T& end() = 0;

        virtual int index(const T& item) = 0;
        virtual bool contains(const T& item) = 0;

        virtual List<T>* sort() = 0;

        void empty() {
            while (size() > 0) {
                pop();
            }
        }

        void mergesort(int left, int right, List<T>& stage) {
            int index = left;
            int segment_length = (right - left);
            if (right != left) {
                if (left + 1 != right) {
                    mergesort(left, left + segment_length / 2, stage);
                    stage.empty();
                    mergesort(right, right + segment_length / 2, stage);
                    stage.empty();
                }
            }
            struct Assign {
                static void from_index(List<T>& merge_to, List<T>* list, int& cursor) {
                    T val = list->operator[](cursor);
                    merge_to.push(val);
                    cursor++;
                }
            };

            {
                int left_limit = left + segment_length;
                int right_limit = right + segment_length;

                // merge from the segment provided
                while (left < left_limit || right < right_limit) {
                    if (left >= left_limit) {
                        Assign::from_index(stage, this, right);
                    } else if (right >= right_limit) {
                        Assign::from_index(stage, this, left);
                    } else {
                        if (this->operator[](left) > this->operator[](right)) {
                            Assign::from_index(stage, this, right);
                        } else {
                            Assign::from_index(stage, this, left);
                        }
                    }
                }

                while (stage.size() > 0) {
                    T val;
                    stage.shift(val);
                    this->operator[](index) = val;
                    index++;
                }
            }
        }
    };
}

#endif //CPPREF_LISTINTERFACE_H
