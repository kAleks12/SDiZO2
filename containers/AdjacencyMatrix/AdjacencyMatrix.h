//
// Created by kacpe on 14.05.2022.
//

#pragma once

#include <cstdlib>
#include "../../utilities/MatrixCell.h"

class AdjacencyMatrix {

public:
    AdjacencyMatrix(const size_t &edgesNumber, const size_t &verticesNumber, const size_t* edgeData);
    ~AdjacencyMatrix();
    void print();
    void prettyPrint();
    size_t getVerticesNumber();
    size_t getEdgesNumber();
    MatrixCell ** getMatrix();


private:
    size_t verticesNumber;
    size_t edgesNumber;
    MatrixCell ** cells;

};