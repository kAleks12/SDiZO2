#pragma once

#include <cstdlib>
#include "MatrixElement.h"

class MatrixGraph {
    size_t nodesNumber;
    size_t edgesNumber;
    MatrixElement ** cells;

public:
    MatrixGraph();
    MatrixGraph(const size_t &edgesNumber, const size_t &nodesNumber, const size_t* edgeData);
    ~MatrixGraph();

    void print();
    size_t getNodesNumber() const;

protected:
    size_t getEdgesNumber() const;
    MatrixElement ** getMatrix();

friend class Algorithms;
};