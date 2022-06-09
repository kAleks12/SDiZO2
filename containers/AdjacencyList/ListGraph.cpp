#include <algorithm>
#include <iostream>
#include "ListGraph.h"
#include "../../utilities/FileOps/FileManagement.h"

ListGraph::ListGraph()
{
    //Initializing with values read from file
    this->edgesNumber = FileManagement::edgesNum;
    this->nodeNumber = FileManagement::nodesNum;
    this->nodeNeighbours = new ListGraphElement* [nodeNumber];

    //Initializing edges list
    for(size_t i = 0; i < nodeNumber; i++){
        nodeNeighbours[i] = nullptr;
    }

    //Setting up provisional variables
    ListGraphElement* currNode;
    size_t currNeighbour;
    size_t currWeight;

    for(size_t i = 0; i < edgesNumber*3; i+= 3){
        //Reading current edge info
        currNode = this->nodeNeighbours[FileManagement::edges[i]];
        currNeighbour =  FileManagement::edges[i + 1];
        currWeight =  FileManagement::edges[i + 2];

        //Checking whether it is the first neighbour
        if(currNode == nullptr){
            this->nodeNeighbours[FileManagement::edges[i]] = new ListGraphElement(currNeighbour, currWeight);
            continue;
        }

        //Iterating through existing neighbours
        while(currNode->nextElement != nullptr){
            currNode = currNode->nextElement;
        }

        //Creating new node's neighbour
        currNode->nextElement = new ListGraphElement(currNeighbour, currWeight);
    }
}

ListGraph::ListGraph(size_t edgesNumber, size_t nodeNumber, size_t *edgesData)
{
    this->edgesNumber = edgesNumber;
    this->nodeNumber = nodeNumber;
    this->nodeNeighbours = new ListGraphElement* [nodeNumber];

    //Initializing edges list
    for(size_t i = 0; i < nodeNumber; i++){
        nodeNeighbours[i] = nullptr;
    }

    //Setting up provisional variables
    ListGraphElement* currNode;
    size_t currNeighbour;
    size_t currWeight;

    for(size_t i = 0; i < edgesNumber*3; i+= 3){
        //Reading current edge info
        currNode = this->nodeNeighbours[edgesData[i]];
        currNeighbour =  edgesData[i + 1];
        currWeight =  edgesData[i + 2];

        //Checking whether it is the first neighbour
        if(currNode == nullptr){
            this->nodeNeighbours[edgesData[i]] = new ListGraphElement(currNeighbour, currWeight);
            continue;
        }

        //Iterating through existing neighbours
        while(currNode->nextElement != nullptr){
            currNode = currNode->nextElement;
        }

        //Creating new node's neighbour
        currNode->nextElement = new ListGraphElement(currNeighbour, currWeight);
    }
}

ListGraph::~ListGraph() {
    if (this->nodeNeighbours != nullptr)
    {
        for (size_t i = 0; i < nodeNumber; i++)
        {
            ListGraphElement* elementToDelete = this->nodeNeighbours[i];

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

            //Deleting each node's list
            while(nextElement->nextElement != nullptr) {
                delete elementToDelete;
                elementToDelete = nextElement;
                nextElement = nextElement->nextElement;
            }
            delete elementToDelete;
            delete nextElement;
        }

        delete[] this->nodeNeighbours;
    }
}


void ListGraph::print() {
    for(size_t i = 0; i < this->nodeNumber; i++)
    {
        std::cout << "Node [" << i << "] : ";
        auto currEdge = this->nodeNeighbours[i];

        while(currEdge != nullptr)
        {
            std::cout << currEdge->node << "(" << currEdge->weight << ") - ";
            currEdge = currEdge->nextElement;
        }

        std::cout << "nullptr\n";
    }
}

size_t ListGraph::getNodesNumber() const {
    return this->nodeNumber;
}

size_t ListGraph::getEdgesNumber() const {
    return this->edgesNumber;
}

ListGraphElement **ListGraph::getList() {
    return this->nodeNeighbours;
}