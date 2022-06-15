#pragma once


#include "../containers/IncidencyMatrix/MatrixGraph.h"
#include "../containers/AdjacencyList/ListGraph.h"
#include "../containers/DynamicArray/MyArray.h"
#include "../utilities/PathElement.h"
#include "../utilities/Results.h"

class Algorithms{
public:
    //MST ALGORITHMS
    static MatrixResult* primMST(MatrixGraph* nodeIndex);
    static ListResult* primMST(ListGraph* nodeIndex);

    static MatrixResult* kruskalMST(MatrixGraph* graph);
    static ListResult* kruskalMST(ListGraph* graph);

    //SHORTEST PATH ALGORITHMS
    static PathResult* dijkstra(MatrixGraph* graph, const size_t &startNode, const size_t &endNode);
    static PathResult* dijkstra(ListGraph* graph, const size_t &start, const size_t &finish);

    static PathResult* bellmanFord(MatrixGraph* graph, const size_t &start, const size_t &finish);
    static PathResult* bellmanFord(ListGraph* graph, const size_t &start, const size_t &finish);
};

