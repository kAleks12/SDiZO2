//
// Created by kacpe on 14.05.2022.
//

#include <iostream>
#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(const size_t & edgesNumber,const size_t & verticesNumber, size_t* edgeData) {
    this->verticesNumber = verticesNumber;
    this->edgesNumber = edgesNumber;

    //Creating 2d table of matrix cells
    this->cells = new MatrixCell* [verticesNumber] ;

    for(size_t i = 0; i < verticesNumber; i++){
        this->cells[i] = new MatrixCell [verticesNumber];
    }

    //Setting operational variables
    size_t currWeight;
    MatrixCell* currVertex;

    //Modifying matrix using edge data
    for(size_t i = 0; i < edgesNumber*3; i+=3)
    {
        currWeight = edgeData[i+2];

        //Modifying origin cell
        currVertex = this->cells[edgeData[i]];
        currVertex[edgeData[i+1]].type = CellType::origin;
        currVertex[edgeData[i+1]].weight = currWeight;

        //Modifying destination cell
        currVertex = (this->cells[edgeData[i+1]]);
        currVertex[edgeData[i+1]].type = CellType::destination;
        currVertex[edgeData[i+1]].weight = currWeight;
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

void AdjacencyMatrix::print() {
    for(size_t i = 0; i < this->verticesNumber; i++)
    {
        std::cout << "Vertex [" << i << "]:\n";
        MatrixCell* currVertex = this->cells[i];

        for(size_t j = 0; j < this->verticesNumber; j++)
        {
            if(currVertex[j].type == CellType::origin) {
                std::cout << "edge to vertex [" << j << "] weight -> " << currVertex[j].weight << "\n";
            }
            /*
            if(currVertex[j].type == CellType::origin) {
                std::cout << 1  << " ";
            }
            if(currVertex[j].type == CellType::destination) {
                std::cout << -1  << " ";
            }
            if(currVertex[j].type == CellType::empty) {
                std::cout << 0  << " ";
            }
            */
        }

        std::cout << "\n";
    }
}
