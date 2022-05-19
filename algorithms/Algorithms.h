//
// Created by kacpe on 19.05.2022.
//

#pragma once


#include "../containers/AdjacencyMatrix/AdjacencyMatrix.h"
#include "../containers/NeighbourhoodList/NeighbourhoodList.h"

class Algorithms {
public:
    static AdjacencyMatrix* primMST(AdjacencyMatrix* graph);
    static NeighbourhoodList* primMST(NeighbourhoodList* graph);
};

