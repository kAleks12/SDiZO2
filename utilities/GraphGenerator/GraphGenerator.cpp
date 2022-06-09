#include <random>
#include <iostream>
#include "GraphGenerator.h"

size_t* GraphGenerator::data = nullptr;
size_t GraphGenerator::edges = 0;



void GraphGenerator::generate(size_t density, size_t nodeNumber, size_t maxValue) {
    //Deleting old graph
    delete [] data;

    size_t minEdgeNum = nodeNumber;
    size_t edgeNumber = (density * nodeNumber * (nodeNumber - 1)) / 200;

    //Checking whether number of edges calculated for entered
    // density and nodes number is not lesser than a minimal
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
    std::uniform_int_distribution<size_t> nodes(0, nodeNumber - 1);

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

    size_t originNode;
    size_t destinationNode;

    //Creating additional random edges
    for (size_t i = minEdgeNum; i < edgeNumber; i++) {
        originNode= nodes(gen);
        destinationNode = nodes(gen);

        while (originNode == destinationNode || isConnected[originNode][destinationNode]) {
            originNode = nodes(gen);
            destinationNode = nodes(gen);
        }

        data[3 * i] = originNode;
        data[3 * i + 1] = destinationNode;
        data[3 * i + 2] = costs(gen);

        isConnected[originNode][destinationNode] = true;
        isConnected[destinationNode][originNode] = true;
    }

    //Freeing allocated memory
    for (size_t i = 0; i < edgeNumber; i++) {
        delete[] isConnected[i];
    }
    delete[] isConnected;

    GraphGenerator::edges = edgeNumber;
}