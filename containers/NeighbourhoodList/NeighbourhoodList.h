//
// Created by kacper on 14.05.2022.
//

#pragma once


#include <cstdlib>
#include "../../utilities/NListElement.h"

class NeighbourhoodList {
public :
    NeighbourhoodList(const size_t &edgesNumber, const size_t &verticesNumber, const size_t edgesData []);
    ~NeighbourhoodList();
    void print();
    size_t getVerticesNumber();
    size_t getEdgesNumber();
    NListElement ** getList();




private:
    size_t edgesNumber;
    size_t verticesNumber;
    NListElement ** verNeighbours;
};

