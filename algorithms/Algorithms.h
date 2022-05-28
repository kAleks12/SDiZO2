//
// Created by kacpe on 19.05.2022.
//

#pragma once


#include "../containers/IncidencyMatrix/IncidencyMatrix.h"
#include "../containers/AdjacencyList/AdjacencyList.h"

class Algorithms {
public:
    static IncidencyMatrix* primMST(IncidencyMatrix* graph);
    static AdjacencyList* primMST(AdjacencyList* graph);
};

