//
// Created by kacpe on 19.05.2022.
//

#pragma once


#include "../containers/IncidencyMatrix/IncidencyMatrix.h"
#include "../containers/AdjacencyList/AdjacencyList.h"
#include "../containers/DynamicArray/DynamicArray.hpp"
#include "../utilities/PathElement.h"
#include "../utilities/Results.h"

class Algorithms {
public:
    //MST ALGORITHMS
    static MatrixMSTResult* primMST(IncidencyMatrix* graph);
    static ListMSTResult* primMST(AdjacencyList* graph);

    static MatrixMSTResult* kruskalMST(IncidencyMatrix* graph);
    static ListMSTResult* kruskalMST(AdjacencyList* graph);

    //SHORTEST PATH ALGORITHMS
    static SPResult* dijkstraPath(IncidencyMatrix* graph, const size_t &start, const size_t &finish);
    static SPResult* dijkstraPath(AdjacencyList* graph, const size_t &start, const size_t &finish);

    static SPResult* BFPath(IncidencyMatrix* graph, const size_t &start, const size_t &finish);
    static SPResult* BFPath(AdjacencyList* graph, const size_t &start, const size_t &finish);
};

