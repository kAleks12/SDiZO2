#pragma once


#include "../containers/IncidencyMatrix/MatrixGraph.h"
#include "../containers/AdjacencyList/ListGraph.h"
#include "../containers/DynamicArray/MyArray.h"
#include "../utilities/PathElement.h"
#include "../utilities/Results.h"

class Algorithms{
public:
    //MST ALGORITHMS
    static MatrixMSTResult* primMST(MatrixGraph* nodeIndex);
    static ListMSTResult* primMST(ListGraph* nodesIndex);

    static MatrixMSTResult* kruskalMST(MatrixGraph* graph);
    static ListMSTResult* kruskalMST(ListGraph* graph);

    //SHORTEST PATH ALGORITHMS
    static SPResult* dijkstraPath(MatrixGraph* graph, const size_t &start, const size_t &finish);
    static SPResult* dijkstraPath(ListGraph* graph, const size_t &start, const size_t &finish);

    static SPResult* bfPath(MatrixGraph* graph, const size_t &start, const size_t &finish);
    static SPResult* bfPath(ListGraph* graph, const size_t &start, const size_t &finish);
};

