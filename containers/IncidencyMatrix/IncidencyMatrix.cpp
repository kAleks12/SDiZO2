//
// Created by kacpe on 14.05.2022.
//

#include <iostream>
#include "IncidencyMatrix.h"
#include "../../utilities/FileOps/FileOps.h"

IncidencyMatrix::IncidencyMatrix()
{
    this->verticesNumber = FileOps::verticesNum;
    this->edgesNumber = FileOps::edgesNum;

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
        currWeight = FileOps::edges[i+2];

        //Checking whether edge is a loop to the same vertex
        if(FileOps::edges[i+1] == FileOps::edges[i]){
            currVertex = this->cells[FileOps::edges[i]];
            currVertex[currColumn].type = CellType::loop;
            currVertex[currColumn].weight = currWeight;

            continue;
        }

        //Modifying origin cell
        currVertex = this->cells[FileOps::edges[i]];
        currVertex[currColumn].type = CellType::origin;
        currVertex[currColumn].weight = currWeight;

        //Modifying destination cell
        currVertex = (this->cells[FileOps::edges[i+1]]);
        currVertex[currColumn].type = CellType::destination;
        currVertex[currColumn].weight = currWeight;
    }

}

IncidencyMatrix::IncidencyMatrix(const size_t & edgesNumber, const size_t & verticesNumber, const size_t* edgeData)
{
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
        size_t orv = edgeData[i];
        currVertex = this->cells[edgeData[i]];
        currVertex[currColumn].type = CellType::origin;
        currVertex[currColumn].weight = currWeight;

        //Modifying destination cell
        size_t destV =  edgeData[i+1];
        currVertex = (this->cells[edgeData[i+1]]);
        currVertex[currColumn].type = CellType::destination;
        currVertex[currColumn].weight = currWeight;
    }

}


IncidencyMatrix::~IncidencyMatrix() {
    if(cells != nullptr) {
        for (size_t i = 0; i < verticesNumber; i++) {
            delete[] this->cells[i];
        }
        delete[] this->cells;
    }
}

void IncidencyMatrix::prettyPrint(){
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

void IncidencyMatrix::print() {
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

size_t IncidencyMatrix::getVerticesNumber() {
    return this->verticesNumber;
}

size_t IncidencyMatrix::getEdgesNumber() {
    return this->edgesNumber;
}

MatrixCell **IncidencyMatrix::getMatrix() {
    return this->cells;
}
