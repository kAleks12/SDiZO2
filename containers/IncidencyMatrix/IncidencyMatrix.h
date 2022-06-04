//
// Created by kacpe on 14.05.2022.
//

#pragma once

#include <cstdlib>
#include "MatrixCell.h"

class IncidencyMatrix {

friend class Algorithms;

public:
    IncidencyMatrix();
    IncidencyMatrix(const size_t &edgesNumber, const size_t &verticesNumber, const size_t* edgeData);
    ~IncidencyMatrix();
    void print();
    void prettyPrint();
    size_t getVerticesNumber();

protected:
    size_t getEdgesNumber();
    MatrixCell ** getMatrix();


private:
    size_t verticesNumber;
    size_t edgesNumber;
    MatrixCell ** cells;

};