//
#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList() {

}

template <typename T>
LinkedList<T>::LinkedList(LinkedList* previous) {
    LinkedList& previousNode = *previous;
    previousNode.next = this;
}

template <typename T>
LinkedList<T>::LinkedList(T nodeData) {
    data = nodeData;
}

template <typename T>
LinkedList<T>::LinkedList(T nodeData, LinkedList* previous) {
    LinkedList& previousNode = *previous;
    previousNode.next = this;
    data = nodeData;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList* previous, T nodeData) {
    data = nodeData;
    LinkedList& previousNode = *previous;
    previousNode.next = this;
}