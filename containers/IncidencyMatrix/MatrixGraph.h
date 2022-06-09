#pragma once

#include <cstdlib>
#include "MatrixElement.h"

class MatrixGraph {
    size_t verticesNumber;
    size_t edgesNumber;
    MatrixElement ** cells;

public:
    MatrixGraph();
    MatrixGraph(const size_t &edgesNumber, const size_t &verticesNumber, const size_t* edgeData);
    ~MatrixGraph();

    void print();
    size_t getVerticesNumber() const;

protected:
    size_t getEdgesNumber() const;
    MatrixElement ** getMatrix();

friend class Algorithms;
};