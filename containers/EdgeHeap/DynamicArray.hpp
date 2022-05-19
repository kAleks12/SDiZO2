//
// Created by kacperA on 14.03.2022.
//

#ifndef SDIZO_PROJECT_1_DYNAMIC_ARRAY_HPP
#define SDIZO_PROJECT_1_DYNAMIC_ARRAY_HPP

#include <iostream>
#include <list>
#include <vector>

template<typename T>
class DynamicArray {
public:

    DynamicArray();

    explicit DynamicArray(const std::list <int> &dataSet);

    ~DynamicArray();

    T &operator[](const size_t &index);


    void addBack(const T &val);

    void addFront(const T &val);

    void add(const T &val, const size_t &position);

    void removeBack();

    void removeFront();

    void remove(const size_t &position);

    bool find(const T &val);

    void print();

private:
    T *head = nullptr;
    size_t size = 0;

};

#include "DynamicArray.tpp"

#endif //SDIZO_PROJECT_1_DYNAMIC_ARRAY_HPP