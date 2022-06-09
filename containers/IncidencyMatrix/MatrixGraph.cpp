#include <iostream>
#include "MatrixGraph.h"
#include "../../utilities/FileOps/FileManagement.h"

MatrixGraph::MatrixGraph() {
    //Assigning with values read from file
    this->nodesNumber = FileManagement::nodesNum;
    this->edgesNumber = FileManagement::edgesNum;

    //Creating 2d table of matrix cells
    this->cells = new MatrixElement *[nodesNumber];

    for (size_t i = 0; i < nodesNumber; i++) {
        this->cells[i] = new MatrixElement[edgesNumber];
    }

    //Setting operational variables
    size_t currWeight;
    size_t currColumn = -1;
    MatrixElement *currNode;

    //Modifying matrix using edge data
    for (size_t i = 0; i < edgesNumber * 3; i += 3) {
        currColumn++;
        currWeight = FileManagement::edges[i + 2];

        //Checking whether edge is a loop to the same node
        if (FileManagement::edges[i + 1] == FileManagement::edges[i]) {
            currNode = this->cells[FileManagement::edges[i]];
            currNode[currColumn].type = CellType::loop;
            currNode[currColumn].weight = currWeight;

            continue;
        }

        //Modifying origin cell
        currNode = this->cells[FileManagement::edges[i]];
        currNode[currColumn].type = CellType::origin;
        currNode[currColumn].weight = currWeight;

        //Modifying destination cell
        currNode = (this->cells[FileManagement::edges[i + 1]]);
        currNode[currColumn].type = CellType::destination;
        currNode[currColumn].weight = currWeight;
    }

}

MatrixGraph::MatrixGraph(const size_t &edgesNumber, const size_t &nodesNumber, const size_t *edgeData) {
    this->nodesNumber = nodesNumber;
    this->edgesNumber = edgesNumber;

    //Creating 2d table of matrix cells
    this->cells = new MatrixElement *[nodesNumber];

    for (size_t i = 0; i < nodesNumber; i++) {
        this->cells[i] = new MatrixElement[edgesNumber];
    }

    //Setting operational variables
    size_t currWeight;
    size_t currColumn = -1;
    MatrixElement *currNode;

    //Modifying matrix using edge data
    for (size_t i = 0; i < edgesNumber * 3; i += 3) {
        currColumn++;
        currWeight = edgeData[i + 2];

        //Checking whether edge is a loop to the same node
        if (edgeData[i + 1] == edgeData[i]) {
            currNode = this->cells[edgeData[i]];
            currNode[currColumn].type = CellType::loop;
            currNode[currColumn].weight = currWeight;

            continue;
        }

        //Modifying origin cell
        size_t orv = edgeData[i];
        currNode = this->cells[edgeData[i]];
        currNode[currColumn].type = CellType::origin;
        currNode[currColumn].weight = currWeight;

        //Modifying destination cell
        size_t destV = edgeData[i + 1];
        currNode = (this->cells[edgeData[i + 1]]);
        currNode[currColumn].type = CellType::destination;
        currNode[currColumn].weight = currWeight;
    }

}

MatrixGraph::~MatrixGraph() {
    //Deleting each node's MatrixCells array
    if (cells != nullptr) {
        for (size_t i = 0; i < nodesNumber; i++) {
            delete[] this->cells[i];
        }

        //Deleting whole matrix array
        delete[] this->cells;
    }
}


void MatrixGraph::print() {
    for (size_t i = 0; i < this->nodesNumber; i++) {
        MatrixElement *currNode = this->cells[i];

        for (size_t j = 0; j < this->edgesNumber; j++) {
            if (currNode[j].type == CellType::loop) {
                std::cout << " " << 2 << " ";
            }
            if (currNode[j].type == CellType::origin) {
                std::cout << " " << 1 << " ";
            }
            if (currNode[j].type == CellType::destination) {
                std::cout << -1 << " ";
            }
            if (currNode[j].type == CellType::empty) {
                std::cout << " " << 0 << " ";
            }

        }

        std::cout << "\n";
    }
}

size_t MatrixGraph::getNodesNumber() const {
    return this->nodesNumber;
}

size_t MatrixGraph::getEdgesNumber() const {
    return this->edgesNumber;
}

MatrixElement **MatrixGraph::getMatrix() {
    return this->cells;
}