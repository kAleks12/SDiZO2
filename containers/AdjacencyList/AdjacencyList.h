//
// Created by kacper on 14.05.2022.
//

#pragma once


#include <cstdlib>
#include "ALElement.h"


class AdjacencyList {

    friend class Algorithms;

public :
    AdjacencyList();
    AdjacencyList(size_t edgesNumber, size_t verticesNumber, const size_t edgesData []);
    ~AdjacencyList();
    void prettyPrint();
    void print();

protected:
    size_t getVerticesNumber() const;
    size_t getEdgesNumber() const;
    ALElement ** getList();


private:
    size_t edgesNumber;
    size_t verticesNumber;
    ALElement ** verNeighbours;
};

