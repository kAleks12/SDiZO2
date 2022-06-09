#pragma once

#include <cmath>
#include "../DynamicArray/MyArray.h"
#include "Edge.h"

class MyHeap {
public:
    Edge extractRoot();
    void add(const Edge& val);
    void print();


private:
    size_t size = 0;
    MyArray<Edge> body;

    static inline int getParent(int index) { return (index - 1) / 2; }

    static inline int getLeft(int index) { return (2 * index + 1); }

    static inline int getRight(int index) { return (2 * index + 2); }

    void minHeapify(int index);

    int getDepth();
};