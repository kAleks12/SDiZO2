//
// Created by kacper on 14.05.2022.
//


#include <iostream>
#include "containers/NeighbourhoodList/NeighbourhoodList.h"
#include "containers/AdjacencyMatrix/AdjacencyMatrix.h"
#include "algorithms/Algorithms.h"

int main(){
    size_t edges[24] = {2, 0, 3,
                        0, 5, 4,
                        1, 0, 7,
                        2, 1, 1,
                        2, 4, 3,
                        3, 2, 6,
                        4, 3, 9,
                        5, 3, 4};


    auto nList = new NeighbourhoodList(8, 6, edges);
    auto aMatrix = new AdjacencyMatrix(8,6, edges);


    auto listMST = Algorithms::primMST(nList);
    auto matrixMST = Algorithms::primMST(aMatrix);

    delete aMatrix;
    delete nList;
    listMST->print();
}