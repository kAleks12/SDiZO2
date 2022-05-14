//
// Created by kacper on 14.05.2022.
//


#include <iostream>
#include "containers/NeighbourhoodList/NeighbourhoodList.h"
#include "containers/AdjacencyMatrix/AdjacencyMatrix.h"

int main(){
    size_t edges[9] = {0, 1, 3, 1, 0, 2, 0, 2, 6};



    while(true) {
        auto nList = new NeighbourhoodList(3, 3, edges);
        nList->print();
        delete nList;


        auto aMatrix = new AdjacencyMatrix(3, 3, edges);
        aMatrix->print();
        delete aMatrix;
    }

}