//
// Created by kacpe on 03.06.2022.
//

#pragma once

#include <vector>
#include "../containers/AdjacencyList/AdjacencyList.h"
#include "../containers/IncidencyMatrix/IncidencyMatrix.h"

class UI {
    static IncidencyMatrix* mGraph;
    static AdjacencyList* lGraph;
    static void MSTSubMenu();
    static void SPSubMenu();
    static void fileGraph();
    static void randomGraph();
    static void displayGraphs();
    static void performPrim();
    static void performKruskal();
    static void performDijkstra(size_t start, size_t finish);
    static void performBF(size_t start, size_t finish);
    static std::vector<size_t> getSPMode();

public:
    static void startMenu();

};


