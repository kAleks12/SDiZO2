#pragma once

#include <iostream>
#include <list>
#include <vector>

template<typename T>
class MyArray {
public:

    MyArray();

    explicit MyArray(const std::list <int> &dataSet);

    ~MyArray();

    T &operator[](const size_t &index);


    void addBack(const T &val);

    void addFront(const T &val);

    void add(const T &val, const size_t &position);

    void removeBack();

    void removeFront();

    void remove(const size_t &position);

    bool find(const T &val);

    void print() const;

    int getSize(){
        return  this->size;
    }

private:
    T *head = nullptr;
    size_t size = 0;

};

#include "MyArray.tpp"