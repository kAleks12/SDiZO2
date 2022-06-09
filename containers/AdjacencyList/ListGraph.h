#pragma once


#include <cstdlib>
#include "ListGraphElement.h"


class ListGraph {
    size_t edgesNumber;
    size_t verticesNumber;
    ListGraphElement ** verNeighbours;

public :
    ListGraph();
    ListGraph(size_t edgesNumber, size_t verticesNumber, size_t* edgesData);
    ~ListGraph();

    void print();
    size_t getVerticesNumber() const;

protected:
    size_t getEdgesNumber() const;
    ListGraphElement ** getList();


    friend class Algorithms;
};

