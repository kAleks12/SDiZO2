#include <algorithm>
#include <iostream>
#include "ListGraph.h"
#include "../../utilities/FileOps/FileManagement.h"

ListGraph::ListGraph()
{
    //Initializing with values read from file
    this->edgesNumber = FileManagement::edgesNum;
    this->verticesNumber = FileManagement::verticesNum;
    this->verNeighbours = new ListGraphElement* [verticesNumber];

    //Initializing edges list
    for(size_t i = 0; i < verticesNumber; i++){
        verNeighbours[i] = nullptr;
    }

    //Setting up provisional variables
    ListGraphElement* currVertex;
    size_t currNeighbour;
    size_t currWeight;

    for(size_t i = 0; i < edgesNumber*3; i+= 3){
        //Reading current edge info
        currVertex = this->verNeighbours[FileManagement::edges[i]];
        currNeighbour =  FileManagement::edges[i + 1];
        currWeight =  FileManagement::edges[i + 2];

        //Checking whether it is the first neighbour
        if(currVertex == nullptr){
            this->verNeighbours[FileManagement::edges[i]] = new ListGraphElement(currNeighbour, currWeight);
            continue;
        }

        //Iterating through existing neighbours
        while(currVertex->nextElement != nullptr){
            currVertex = currVertex->nextElement;
        }

        //Creating new vertex's neighbour
        currVertex->nextElement = new ListGraphElement(currNeighbour, currWeight);
    }
}

ListGraph::ListGraph(size_t edgesNumber, size_t verticesNumber, size_t *edgesData)
{
    this->edgesNumber = edgesNumber;
    this->verticesNumber = verticesNumber;
    this->verNeighbours = new ListGraphElement* [verticesNumber];

    //Initializing edges list
    for(size_t i = 0; i < verticesNumber; i++){
        verNeighbours[i] = nullptr;
    }

    //Setting up provisional variables
    ListGraphElement* currVertex;
    size_t currNeighbour;
    size_t currWeight;

    for(size_t i = 0; i < edgesNumber*3; i+= 3){
        //Reading current edge info
        currVertex = this->verNeighbours[edgesData[i]];
        currNeighbour =  edgesData[i + 1];
        currWeight =  edgesData[i + 2];

        //Checking whether it is the first neighbour
        if(currVertex == nullptr){
            this->verNeighbours[edgesData[i]] = new ListGraphElement(currNeighbour, currWeight);
            continue;
        }

        //Iterating through existing neighbours
        while(currVertex->nextElement != nullptr){
            currVertex = currVertex->nextElement;
        }

        //Creating new vertex's neighbour
        currVertex->nextElement = new ListGraphElement(currNeighbour, currWeight);
    }
}

ListGraph::~ListGraph() {
    if (this->verNeighbours != nullptr)
    {
        for (size_t i = 0; i < verticesNumber; i++)
        {
            ListGraphElement* elementToDelete = this->verNeighbours[i];

            if(elementToDelete == nullptr)
            {
                continue;
            }

            if(elementToDelete->nextElement == nullptr)
            {
                delete elementToDelete;
                continue;
            }

            ListGraphElement* nextElement = elementToDelete->nextElement;

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


void ListGraph::print() {
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

size_t ListGraph::getVerticesNumber() const {
    return this->verticesNumber;
}

size_t ListGraph::getEdgesNumber() const {
    return this->edgesNumber;
}

ListGraphElement **ListGraph::getList() {
    return this->verNeighbours;
}