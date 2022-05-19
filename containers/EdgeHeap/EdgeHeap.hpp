//
// Created by kacper on 18.03.2022.
//

#pragma once

#include <cmath>
#include "DynamicArray.hpp"
#include "../../utilities/Edge.h"

class EdgeHeap {
public:
    Edge extractRoot();
    void add(const Edge& val);
    void print();


private:
    size_t size = 0;
    DynamicArray<Edge> body;

    inline int getParent(int index) { return (index - 1) / 2; }

    inline int getLeft(int index) { return (2 * index + 1); }

    inline int getRight(int index) { return (2 * index + 2); }

    void minHeapify(int index);

    int getDepth();
};