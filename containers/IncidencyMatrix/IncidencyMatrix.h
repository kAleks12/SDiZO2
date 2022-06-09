//
// Created by kacpe on 14.05.2022.
//

#pragma once

#include <cstdlib>
#include "MatrixCell.h"

class IncidencyMatrix {
    //Class variables
    size_t verticesNumber;
    size_t edgesNumber;
    MatrixCell ** cells;

public:
    //Class methods
    IncidencyMatrix(); //Default constructor
    IncidencyMatrix(const size_t &edgesNumber, const size_t &verticesNumber, const size_t* edgeData); //Normal contructor
    ~IncidencyMatrix(); //Destructor

    void print(); //Print matrix
    size_t getVerticesNumber() const; //Return number of matrix's vertices

protected:
    size_t getEdgesNumber() const; //Return number of matrix's edges
    MatrixCell ** getMatrix(); //Return 2d table of matrix cells

friend class Algorithms;
};