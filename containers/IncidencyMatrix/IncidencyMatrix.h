//
// Created by kacpe on 14.05.2022.
//

#pragma once

#include <cstdlib>
#include "MatrixCell.h"

class IncidencyMatrix {
    size_t verticesNumber;
    size_t edgesNumber;
    MatrixCell ** cells;

public:
    IncidencyMatrix();
    IncidencyMatrix(const size_t &edgesNumber, const size_t &verticesNumber, const size_t* edgeData);
    ~IncidencyMatrix();

    void print();
    size_t getVerticesNumber() const;

protected:
    size_t getEdgesNumber() const;
    MatrixCell ** getMatrix();

friend class Algorithms;
};