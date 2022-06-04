//
// Created by kacper on 14.05.2022.
//

#pragma once


#include <cstdlib>
#include "ALElement.h"


class AdjacencyList {
    size_t edgesNumber;
    size_t verticesNumber;
    ALElement ** verNeighbours;

public :
    AdjacencyList();
    AdjacencyList(size_t edgesNumber, size_t verticesNumber, size_t* edgesData);
    ~AdjacencyList();

    void print();
    size_t getVerticesNumber() const;

protected:
    size_t getEdgesNumber() const;
    ALElement ** getList();


    friend class Algorithms;
};

