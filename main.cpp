//
// Created by kacper on 14.05.2022.
//


#include <iostream>
#include "containers/AdjacencyList/AdjacencyList.h"
#include "containers/IncidencyMatrix/IncidencyMatrix.h"
#include "algorithms/Algorithms.h"

int main() {
    size_t edges[44] = {0, 1, 8,
                        0, 4, 1,
                        4, 1, 6,
                        1, 3, 1,
                        1, 2, 1,
                        4, 2, 1,
                        4, 5, 3,
                        2, 5, 1,
                        3, 6, 0,
                        6, 1, 1,
                        7, 2, 0,
                        5, 7, 1,
                        7, 6, 1,
                        2, 6, 4};


    auto aList = new AdjacencyList(14, 8, edges);
    auto iMatrix = new IncidencyMatrix(14, 8, edges);

    auto result = Algorithms::dijkstraPath(aList, 0, 7);
    result.display();

}