//
// Created by kacpe on 01.06.2022.
//

#pragma once

#include <iostream>
#include <utility>
#include "../containers/IncidencyMatrix/IncidencyMatrix.h"
#include "../containers/AdjacencyList/AdjacencyList.h"

///////////////////////////////
//    FILE STORES VARIOUS    //
//    STRUCTURES  FOR        //
//    ALGORITHMS' RESULTS    //
///////////////////////////////


//Structure for results of MST algorithms which use matrix representation
struct MatrixMSTResult{
    IncidencyMatrix* output;
    size_t cost;

    MatrixMSTResult(IncidencyMatrix* matrix, size_t cost): output(matrix), cost(cost)
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
    AdjacencyList* output;
    size_t cost;

    ListMSTResult(AdjacencyList* list, size_t cost): output(list), cost(cost)
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