//
// Created by kacper on 18.03.2022.
//

#pragma once

#include <cmath>
#include "../DynamicArray/DynamicArray.hpp"
#include "Edge.h"

class EdgeHeap {
    //Class variables
    size_t size = 0;
    DynamicArray<Edge> body;

public:
    //Class methods
    Edge extractRoot(); //Delete root from heap and return it
    void add(const Edge& val); //Add edge to heap

private:
    static inline int getParent(int index) { return (index - 1) / 2; } //Calculate parent index of provided index

    static inline int getLeft(int index) { return (2 * index + 1); } //Calculate left child index of provided index

    static inline int getRight(int index) { return (2 * index + 2); } //Calculate right child index of provided index

    void minHeapify(int index); //Function used to add value to heap
};