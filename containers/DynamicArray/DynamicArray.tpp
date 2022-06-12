//
// Created by kacper on 14.03.2022.
//

#include <fstream>

template<typename T>
DynamicArray<T>::DynamicArray() {
    //Initializing head
    this->head = new T[0];

    this->size = 0;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    //Deleting head if it exists
    if (this->head != nullptr) {
        delete[] this->head;
    }
}

template<typename T>
T &DynamicArray<T>::operator[](const size_t &index) {
    //Checking whether index is in bounds of array
    if (index > this->size) {
        throw std::out_of_range("Out of range exception!");
    }

    return *(this->head + index);
}

template<typename T>
void DynamicArray<T>::addBack(const T &val) {
    //Creating new head
    T *newHead = new T[this->size + 1];

    //Restoring elements from the old table
    if (this->size > 0) {
        for (int i = 0; i < this->size; i++) {
            newHead[i] = this->head[i];
        }
    }

    //Setting new element
    newHead[this->size] = val;

    //Deleting old head and swapping it for the new one
    delete[] this->head;
    this->head = newHead;
    this->size++;
}

template<typename T>
void DynamicArray<T>::addFront(const T &val) {
    //Creating new head
    T *newHead = new T[this->size + 1];

    //Setting value
    newHead[0] = val;

    //restoring elements from old array
    if (this->size > 0) {
        for (int i = 1; i <= this->size; i++) {
            newHead[i] = this->head[i - 1];
        }
    }

    //Deleting old head and swapping it for the new one
    delete[] this->head;
    this->head = newHead;
    this->size++;
}

template<typename T>
void DynamicArray<T>::removeBack() {
    //Checking whether array is empty
    if (this->size == 0) {
        return;
    }

    //Creating new head
    T *newHead = new T[this->size - 1];

    //Restoring old elements without the last one
    for (int i = 0; i < this->size - 1; i++) {
        newHead[i] = this->head[i];
    }

    //Deleting old head and swapping it for the new one
    delete[] this->head;
    this->head = newHead;
    this->size--;
}

template<typename T>
void DynamicArray<T>::removeFront() {
    //Checking whether array is empty
    if (this->size == 0) {
        return;
    }

    //Creating new head
    T *newHead = new T[this->size - 1];

    //Restoring old elements without the first one
    for (int i = 0; i < this->size - 1; i++) {
        newHead[i] = this->head[i + 1];
    }

    //Deleting old head and swapping it for the new one
    delete[] this->head;
    this->head = newHead;
    this->size--;
}