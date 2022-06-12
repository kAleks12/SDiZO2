//
// Created by kacper on 14.05.2022.
//

#include <algorithm>
#include <iostream>
#include "AdjacencyList.hpp"
#include "../../utilities/FileOps/FileOps.hpp"

AdjacencyList::AdjacencyList()
{
    //Initializing with values read from file
    this->edgesNumber = FileOps::edgesNum;
    this->verticesNumber = FileOps::verticesNum;
    this->verNeighbours = new ALElement* [verticesNumber];

    //Initializing edges list
    for(size_t i = 0; i < verticesNumber; i++){
        verNeighbours[i] = nullptr;
    }

    //Setting up provisional variables
    ALElement* currVertex;
    size_t currNeighbour;
    size_t currWeight;

    for(size_t i = 0; i < edgesNumber*3; i+= 3){
        //Reading current edge info
        currVertex = this->verNeighbours[FileOps::edges[i]];
        currNeighbour =  FileOps::edges[i + 1];
        currWeight =  FileOps::edges[i + 2];

        //Checking whether it is the first neighbour
        if(currVertex == nullptr){
            this->verNeighbours[FileOps::edges[i]] = new ALElement(currNeighbour, currWeight);
            continue;
        }

        //Iterating through existing neighbours
        while(currVertex->nextElement != nullptr){
            currVertex = currVertex->nextElement;
        }

        //Creating new vertex's neighbour
        currVertex->nextElement = new ALElement(currNeighbour, currWeight);
    }
}

AdjacencyList::AdjacencyList(size_t edgesNumber, size_t verticesNumber, size_t *edgesData)
{
    this->edgesNumber = edgesNumber;
    this->verticesNumber = verticesNumber;
    this->verNeighbours = new ALElement* [verticesNumber];

    //Initializing edges list
    for(size_t i = 0; i < verticesNumber; i++){
        verNeighbours[i] = nullptr;
    }

    //Setting up provisional variables
    ALElement* currVertex;
    size_t currNeighbour;
    size_t currWeight;

    for(size_t i = 0; i < edgesNumber*3; i+= 3){
        //Reading current edge info
        currVertex = this->verNeighbours[edgesData[i]];
        currNeighbour =  edgesData[i + 1];
        currWeight =  edgesData[i + 2];

        //Checking whether it is the first neighbour
        if(currVertex == nullptr){
            this->verNeighbours[edgesData[i]] = new ALElement(currNeighbour, currWeight);
            continue;
        }

        //Iterating through existing neighbours
        while(currVertex->nextElement != nullptr){
            currVertex = currVertex->nextElement;
        }

        //Creating new vertex's neighbour
        currVertex->nextElement = new ALElement(currNeighbour, currWeight);
    }
}

AdjacencyList::~AdjacencyList() {
    if (this->verNeighbours != nullptr)
    {
        for (size_t i = 0; i < verticesNumber; i++)
        {
            ALElement* elementToDelete = this->verNeighbours[i];

            if(elementToDelete == nullptr)
            {
                continue;
            }

            if(elementToDelete->nextElement == nullptr)
            {
                delete elementToDelete;
                continue;
            }

            ALElement* nextElement = elementToDelete->nextElement;

            //Deleting each vertex's list
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


void AdjacencyList::print() {
    for(size_t i = 0; i < this->verticesNumber; i++)
    {
        std::cout << "Vertex [" << i << "] : ";
        auto currEdge = this->verNeighbours[i];

        while(currEdge != nullptr)
        {
            std::cout <<  currEdge->vertex << "(" << currEdge->weight << ") - ";
            currEdge = currEdge->nextElement;
        }

        std::cout << "nullptr\n";
    }
}

size_t AdjacencyList::getVerticesNumber() const {
    return this->verticesNumber;
}

size_t AdjacencyList::getEdgesNumber() const {
    return this->edgesNumber;
}

ALElement **AdjacencyList::getList() {
    return this->verNeighbours;
}