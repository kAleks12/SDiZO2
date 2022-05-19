//
// Created by kacpe on 14.05.2022.
//

#include <iostream>
#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(const size_t & edgesNumber,const size_t & verticesNumber, const size_t* edgeData) {
    this->verticesNumber = verticesNumber;
    this->edgesNumber = edgesNumber;

    //Creating 2d table of matrix cells
    this->cells = new MatrixCell* [verticesNumber] ;

    for(size_t i = 0; i < verticesNumber; i++){
        this->cells[i] = new MatrixCell [edgesNumber];
    }

    //Setting operational variables
    size_t currWeight;
    size_t currColumn = -1;
    MatrixCell* currVertex;

    //Modifying matrix using edge data
    for(size_t i = 0; i < edgesNumber*3; i+=3)
    {
        currColumn ++;
        currWeight = edgeData[i+2];

        //Checking whether edge is a loop to the same vertex
        if(edgeData[i+1] == edgeData[i]){
            currVertex = this->cells[edgeData[i]];
            currVertex[currColumn].type = CellType::loop;
            currVertex[currColumn].weight = currWeight;

            continue;
        }

        //Modifying origin cell
        currVertex = this->cells[edgeData[i]];
        currVertex[currColumn].type = CellType::origin;
        currVertex[currColumn].weight = currWeight;

        //Modifying destination cell
        currVertex = (this->cells[edgeData[i+1]]);
        currVertex[currColumn].type = CellType::destination;
        currVertex[currColumn].weight = currWeight;
    }

}

AdjacencyMatrix::~AdjacencyMatrix() {
    if(cells != nullptr) {
        for (size_t i = 0; i < verticesNumber; i++) {
            delete[] this->cells[i];
        }
        delete[] this->cells;
    }
}

void AdjacencyMatrix::prettyPrint(){
    for(size_t i = 0; i < this->verticesNumber; i++) {
        std::cout << "Vertex [" << i << "]:\n";
        MatrixCell* currVertex = this->cells[i];


        for (size_t j = 0; j < this->edgesNumber; j++) {
            if (currVertex[j].type == CellType::origin || currVertex[j].type == CellType::loop) {
                std::cout << "edge to vertex [" << j << "] weight -> " << currVertex[j].weight << "\n";
            }
        }

        std::cout << "\n";
    }
}

void AdjacencyMatrix::print() {
    for(size_t i = 0; i < this->verticesNumber; i++)
    {
        MatrixCell* currVertex = this->cells[i];

        for(size_t j = 0; j < this->edgesNumber; j++)
        {
            if(currVertex[j].type == CellType::loop) {
                std::cout << " " << 2  << " ";
            }
            if(currVertex[j].type == CellType::origin) {
                std::cout << " " << 1  << " ";
            }
            if(currVertex[j].type == CellType::destination) {
                std::cout << -1  << " ";
            }
            if(currVertex[j].type == CellType::empty) {
                std::cout << " " << 0  << " ";
            }

        }

        std::cout << "\n";
    }
}

size_t AdjacencyMatrix::getVerticesNumber() {
    return this->verticesNumber;
}

size_t AdjacencyMatrix::getEdgesNumber() {
    return this->edgesNumber;
}

MatrixCell **AdjacencyMatrix::getMatrix() {
    return this->cells;
}
