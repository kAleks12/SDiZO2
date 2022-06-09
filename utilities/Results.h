#pragma once

#include <iostream>
#include <utility>
#include "../containers/IncidencyMatrix/MatrixGraph.h"
#include "../containers/AdjacencyList/ListGraph.h"

//Structure for results of MST algorithms which use matrix representation
struct MatrixMSTResult{
    MatrixGraph* output;
    size_t cost;

    MatrixMSTResult(MatrixGraph* matrix, size_t cost): output(matrix), cost(cost)
    {}

    ~MatrixMSTResult(){
        delete output;
    }

    void display() const
    {
        output->print();
        std::cout << "\nTotal MST cost: " << this->cost << "\n";;
    }

};

//Structure for results of MST algorithms which use list representation
struct ListMSTResult{
    ListGraph* output;
    size_t cost;

    ListMSTResult(ListGraph* list, size_t cost): output(list), cost(cost)
    {}

    ~ListMSTResult(){
        delete output;
    }

    void display() const
    {
        this->output->print();
        std::cout << "\nTotal MST cost: " << this->cost << "\n";
    }
};


//Structure for results of SP algorithms
struct SPResult{
    std::string  path;
    size_t cost;

    SPResult( std::string path, size_t cost): path(std::move(path)), cost(cost)
    {}

    void display() const
    {
        if(this->path != "")
        {
            std::cout << this->path << std::endl;
            std::cout << "Total path cost: " << this->cost << "\n\n";
        }
        else
            std::cout << "Path does not exist\n";
    }
};