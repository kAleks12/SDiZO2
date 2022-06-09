//
// Created by kacpe on 03.06.2022.
//

#pragma once

#include <vector>
#include "../containers/AdjacencyList/AdjacencyList.h"
#include "../containers/IncidencyMatrix/IncidencyMatrix.h"

class UI {
    //Class variables
    static IncidencyMatrix* mGraph;
    static AdjacencyList* lGraph;

    //Class methods
    static void MSTSubMenu();
    static void SPSubMenu();

    static void fileGraph(); //Wizard for creating graph from file
    static void randomGraph(); //Wizard for creating random graph
    static std::vector<size_t> getSPMode(); //Wizard for selecting vertices pair for SP algorithms

    static void displayGraphs();

    static void performPrim();
    static void performKruskal();

    static void performDijkstra(size_t start, size_t finish);
    static void performBF(size_t start, size_t finish);


public:
    static void startMenu();
};


