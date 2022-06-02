//
// Created by kacper on 14.05.2022.
//

#pragma once


#include <cstdlib>
#include "ALElement.h"

class AdjacencyList {
public :
    AdjacencyList(const size_t &edgesNumber, const size_t &verticesNumber, const size_t edgesData []);
    ~AdjacencyList();
    void prettyPrint();
    void print();
    size_t getVerticesNumber();
    size_t getEdgesNumber();
    ALElement ** getList();




private:
    size_t edgesNumber;
    size_t verticesNumber;
    ALElement ** verNeighbours;
};

