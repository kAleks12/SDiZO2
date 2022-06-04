//
// Created by kacpe on 03.06.2022.
//

#include <random>
#include <iostream>
#include "GraphGenerator.h"

size_t* GraphGenerator::data = nullptr;
size_t GraphGenerator::edges = 0;



void GraphGenerator::generate(size_t density, size_t vertexNumber, size_t maxValue) {
    //Deleting old graph
    delete [] data;

    size_t minEdgeNum = vertexNumber;
    size_t edgeNumber = (density * vertexNumber * (vertexNumber - 1)) / 200;

    //Checking whether number of edges calculated for entered
    // density and vertices number is not lesser than a minimal
    // number of edges for a connected graph
    if(edgeNumber < minEdgeNum){
        edgeNumber = minEdgeNum;
    }

    size_t dataSize = 3 * edgeNumber;
    data = new size_t[dataSize];

    //Setting up random library to generate edges and weights
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> costs(1, maxValue);
    std::uniform_int_distribution<size_t> vertices(0, vertexNumber - 1);

    //Creating 2d table to store information about created edges
    bool **isConnected = new bool *[edgeNumber];
    for (size_t i = 0; i < edgeNumber; i++) {

        isConnected[i] = new bool[edgeNumber];
        for (size_t j = 0; j < edgeNumber; j++) {
            isConnected[i][j] = false;
        }
    }

    //Creating initial ring
    for (size_t i = 0; i < minEdgeNum; i++) {
        if(i == minEdgeNum-1)
        {
            data[3 * i] = i;
            data[3 * i + 1] = 0;
            data[3 * i + 2] = costs(gen);
            isConnected[i][0] = true;
            isConnected[0][i] = true;
            continue;
        }

        data[3 * i] = i;
        data[3 * i + 1] = i + 1;
        data[3 * i + 2] = costs(gen);
        isConnected[i][i + 1] = true;
        isConnected[i + 1][i] = true;
    }

    size_t originV;
    size_t destinationV;

    //Creating additional random edges
    for (size_t i = minEdgeNum; i < edgeNumber; i++) {
        originV= vertices(gen);
        destinationV = vertices(gen);

        while (originV == destinationV || isConnected[originV][destinationV]) {
            originV = vertices(gen);
            destinationV = vertices(gen);
        }

        data[3 * i] = originV;
        data[3 * i + 1] = destinationV;
        data[3 * i + 2] = costs(gen);

        isConnected[originV][destinationV] = true;
        isConnected[destinationV][originV] = true;
    }

    //Freeing allocated memory
    for (size_t i = 0; i < edgeNumber; i++) {
        delete[] isConnected[i];
    }
    delete[] isConnected;

    GraphGenerator::edges = edgeNumber;
}