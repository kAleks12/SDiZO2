#pragma once

#include <vector>
#include "../containers/AdjacencyList/ListGraph.h"
#include "../containers/IncidencyMatrix/MatrixGraph.h"

class Interface {
    static MatrixGraph* mGraph;
    static ListGraph* lGraph;

    static void MSTSubMenu();
    static void SPSubMenu();

    static void fileGraph();
    static void randomGraph();
    static void displayGraphs();

    static void doPrim();
    static void doKruskal();

    static void doDijkstra(size_t start, size_t finish);
    static void doBelmanFord(size_t start, size_t finish);

    static std::vector<size_t> getShortestPathMode();

public:
    static void startMenu();

};


