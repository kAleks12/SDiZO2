//
// Created by kacper on 14.05.2022.
//


#include <iostream>
#include "utilities/FileOps.h"
#include "containers/AdjacencyList/AdjacencyList.h"
#include "containers/IncidencyMatrix/IncidencyMatrix.h"
#include "algorithms/Algorithms.h"

int main() {

    FileOps::readData("graph.txt");

    auto aList = new IncidencyMatrix();
    auto result = Algorithms::primMST(aList);
    result->display();
    delete aList;
}