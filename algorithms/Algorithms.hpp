//
// Created by kacpe on 19.05.2022.
//

#pragma once


#include "../containers/IncidencyMatrix/IncidencyMatrix.hpp"
#include "../containers/AdjacencyList/AdjacencyList.hpp"
#include "../containers/DynamicArray/DynamicArray.hpp"
#include "../utilities/PathElement.hpp"
#include "../utilities/Results.hpp"

class Algorithms{
public:
    //MST ALGORITHMS
    static MatrixMSTResult* primMST(IncidencyMatrix* graph);
    static ListMSTResult* primMST(AdjacencyList* graph);

    static MatrixMSTResult* kruskalMST(IncidencyMatrix* graph);
    static ListMSTResult* kruskalMST(AdjacencyList* graph);

    //SHORTEST PATH ALGORITHMS
    static SPResult* dijkstraPath(IncidencyMatrix* graph, const size_t &start, const size_t &finish);
    static SPResult* dijkstraPath(AdjacencyList* graph, const size_t &start, const size_t &finish);

    static SPResult* bfPath(IncidencyMatrix* graph, const size_t &start, const size_t &finish);
    static SPResult* bfPath(AdjacencyList* graph, const size_t &start, const size_t &finish);
};

