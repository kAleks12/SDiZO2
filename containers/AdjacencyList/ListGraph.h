#pragma once


#include <cstdlib>
#include "ListGraphElement.h"


class ListGraph {
    size_t edgesNumber;
    size_t nodeNumber;
    ListGraphElement ** nodeNeighbours;

public :
    ListGraph();
    ListGraph(size_t edgesNumber, size_t nodeNumber, size_t* edgesData);
    ~ListGraph();

    void print();
    size_t getNodesNumber() const;

protected:
    size_t getEdgesNumber() const;
    ListGraphElement ** getList();


    friend class Algorithms;
};

