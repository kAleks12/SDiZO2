//
// Created by kacper on 14.05.2022.
//

#include <algorithm>
#include <iostream>
#include "NeighbourhoodList.h"


NeighbourhoodList::NeighbourhoodList(const size_t &edgesNumber, const size_t &verticesNumber, const size_t *edgesData) {
    this->edgesNumber = edgesNumber;
    this->verticesNumber = verticesNumber;
    this->verNeighbours = new NListElement* [verticesNumber];

    //Initializing edges list
    for(size_t i = 0; i < verticesNumber; i++){
        verNeighbours[i] = nullptr;
    }

    //Setting up provisional variables
    NListElement* currVertex;
    size_t currNeighbour;
    size_t currWeight;

    for(size_t i = 0; i < edgesNumber*3; i+= 3){
        //Reading current edge info
        currVertex = this->verNeighbours[edgesData[i]];
        currNeighbour =  edgesData[i + 1];
        currWeight =  edgesData[i + 2];

        //Checking whether it is the first neighbour
        if(currVertex == nullptr){
            this->verNeighbours[edgesData[i]] = new NListElement(currNeighbour, currWeight);
            continue;
        }

        //Iterating through existing neighbours
        while(currVertex->nextElement != nullptr){
            currVertex = currVertex->nextElement;
        }

        //Creating new vertex's neighbour
        currVertex->nextElement = new NListElement(currNeighbour, currWeight);
    }
}

NeighbourhoodList::~NeighbourhoodList() {
    if (this->verNeighbours != nullptr)
    {
        for (size_t i = 0; i < verticesNumber; i++)
        {
            NListElement* elementToDelete = this->verNeighbours[i];

            if(elementToDelete == nullptr)
            {
                continue;
            }

            if(elementToDelete->nextElement == nullptr)
            {
                delete elementToDelete;
                continue;
            }

            NListElement* nextElement = elementToDelete->nextElement;

            while(nextElement->nextElement != nullptr) {
                delete elementToDelete;
                elementToDelete = nextElement;
                nextElement = nextElement->nextElement;
            }
            delete elementToDelete;
            delete nextElement;
        }
        delete[] this->verNeighbours;
    }
}

void NeighbourhoodList::print() {
    for(size_t i = 0; i < this->verticesNumber; i++)
    {
        std::cout << "Vertex [" << i << "]:\n";
        auto currEdge = this->verNeighbours[i];

        while(currEdge != nullptr)
        {
            std::cout << "edge to vertex [" << currEdge->vertex << "] weight -> " << currEdge->weight << "\n";
            currEdge = currEdge->nextElement;
        }

        std::cout << "\n";
    }
}

size_t NeighbourhoodList::getVerticesNumber() {
    return this->verticesNumber;
}

size_t NeighbourhoodList::getEdgesNumber() {
    return this->edgesNumber;
}

NListElement **NeighbourhoodList::getList() {
    return this->verNeighbours;
}
