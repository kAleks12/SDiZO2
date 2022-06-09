#include <iostream>
#include "MatrixGraph.h"
#include "../../utilities/FileOps/FileManagement.h"

MatrixGraph::MatrixGraph()
{
    //Assigning with values read from file
    this->verticesNumber = FileManagement::verticesNum;
    this->edgesNumber = FileManagement::edgesNum;

    //Creating 2d table of matrix cells
    this->cells = new MatrixElement* [verticesNumber] ;

    for(size_t i = 0; i < verticesNumber; i++){
        this->cells[i] = new MatrixElement [edgesNumber];
    }

    //Setting operational variables
    size_t currWeight;
    size_t currColumn = -1;
    MatrixElement* currVertex;

    //Modifying matrix using edge data
    for(size_t i = 0; i < edgesNumber*3; i+=3)
    {
        currColumn ++;
        currWeight = FileManagement::edges[i + 2];

        //Checking whether edge is a loop to the same vertex
        if(FileManagement::edges[i + 1] == FileManagement::edges[i]){
            currVertex = this->cells[FileManagement::edges[i]];
            currVertex[currColumn].type = CellType::loop;
            currVertex[currColumn].weight = currWeight;

            continue;
        }

        //Modifying origin cell
        currVertex = this->cells[FileManagement::edges[i]];
        currVertex[currColumn].type = CellType::origin;
        currVertex[currColumn].weight = currWeight;

        //Modifying destination cell
        currVertex = (this->cells[FileManagement::edges[i + 1]]);
        currVertex[currColumn].type = CellType::destination;
        currVertex[currColumn].weight = currWeight;
    }

}

MatrixGraph::MatrixGraph(const size_t & edgesNumber, const size_t & verticesNumber, const size_t* edgeData)
{
    this->verticesNumber = verticesNumber;
    this->edgesNumber = edgesNumber;

    //Creating 2d table of matrix cells
    this->cells = new MatrixElement* [verticesNumber] ;

    for(size_t i = 0; i < verticesNumber; i++){
        this->cells[i] = new MatrixElement [edgesNumber];
    }

    //Setting operational variables
    size_t currWeight;
    size_t currColumn = -1;
    MatrixElement* currVertex;

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

MatrixGraph::~MatrixGraph() {
    //Deleting each vertex's MatrixCells array
    if(cells != nullptr) {
        for (size_t i = 0; i < verticesNumber; i++) {
            delete[] this->cells[i];
        }

        //Deleting whole matrix array
        delete[] this->cells;
    }
}



void MatrixGraph::print() {
    for(size_t i = 0; i < this->verticesNumber; i++)
    {
        MatrixElement* currVertex = this->cells[i];

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

size_t MatrixGraph::getVerticesNumber() const {
    return this->verticesNumber;
}

size_t MatrixGraph::getEdgesNumber() const {
    return this->edgesNumber;
}

MatrixElement **MatrixGraph::getMatrix() {
    return this->cells;
}