//
// Created by kacper on 14.05.2022.
//

#pragma once


#include <cstdlib>
#include "ALElement.h"


class AdjacencyList {
    //Class variables
    size_t edgesNumber;
    size_t verticesNumber;
    ALElement ** verNeighbours;

    //Class methods
public:
    AdjacencyList();
    AdjacencyList(size_t edgesNumber, size_t verticesNumber, size_t* edgesData);
    ~AdjacencyList();

    void print(); //Print list
    size_t getVerticesNumber() const; //Return number of list's vertices

protected:
    size_t getEdgesNumber() const; //Return number of list's edges
    ALElement ** getList(); //Return 2d table of list elements


    friend class Algorithms;
};

