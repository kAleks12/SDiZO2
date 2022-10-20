//
// Created by kacpe on 03.06.2022.
//

#include <random>
#include <iostream>
#include "GraphGenerator.hpp"

size_t *GraphGenerator::edgesT = nullptr;
size_t GraphGenerator::edgesNum = 0;


void GraphGenerator::generate(size_t density, size_t vertexNumber, size_t maxValue) {
    size_t minEdgeNum = vertexNumber;
    size_t edgeNumber = (density * vertexNumber * (vertexNumber - 1)) / 200;

    //Checking whether number of edgesNum calculated for entered
    // density and vertices number is not lesser than a minimal
    // number of edgesNum for a connected graph
    if (edgeNumber < minEdgeNum) {
        edgeNumber = minEdgeNum;
    }

    size_t dataSize = 3 * edgeNumber;
    edgesT = new size_t[dataSize];

    //Setting up random library to generate edgesNum and weights
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> costs(1, maxValue);
    std::uniform_int_distribution<size_t> vertices(0, vertexNumber - 1);

    //Creating 2d table to store information about created edgesNum
    bool **isConnected = new bool *[edgeNumber];
    for (size_t i = 0; i < edgeNumber; i++) {

        isConnected[i] = new bool[edgeNumber];
        for (size_t j = 0; j < edgeNumber; j++) {
            isConnected[i][j] = false;
        }
    }

    //Creating initial ring
    for (size_t i = 0; i < minEdgeNum; i++) {
        if (i == minEdgeNum - 1) {
            edgesT[3 * i] = i;
            edgesT[3 * i + 1] = 0;
            edgesT[3 * i + 2] = costs(gen);
            isConnected[i][0] = true;
            isConnected[0][i] = true;
            continue;
        }

        edgesT[3 * i] = i;
        edgesT[3 * i + 1] = i + 1;
        edgesT[3 * i + 2] = costs(gen);
        isConnected[i][i + 1] = true;
        isConnected[i + 1][i] = true;
    }

    size_t originV;
    size_t destinationV;

    //Creating additional random edgesNum
    for (size_t i = minEdgeNum; i < edgeNumber; i++) {
        originV = vertices(gen);
        destinationV = vertices(gen);

        while (originV == destinationV || isConnected[originV][destinationV]) {
            originV = vertices(gen);
            destinationV = vertices(gen);
        }

        edgesT[3 * i] = originV;
        edgesT[3 * i + 1] = destinationV;
        edgesT[3 * i + 2] = costs(gen);

        isConnected[originV][destinationV] = true;
        isConnected[destinationV][originV] = true;
    }

    //Freeing allocated memory
    for (size_t i = 0; i < edgeNumber; i++) {
        delete[] isConnected[i];
    }
    delete[] isConnected;

    GraphGenerator::edgesNum = edgeNumber;
}

void GraphGenerator::clear() {
    delete[] edgesT;
}