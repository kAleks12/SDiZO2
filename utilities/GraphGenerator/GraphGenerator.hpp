//
// Created by kacper on 03.06.2022.
//

#pragma once

class GraphGenerator {

public:
    //Class variables
    static size_t* edgesT;
    static size_t edgesNum;

    //Class methods
    static void generate(size_t density, size_t vertexNumber, size_t maxValue); //Generate random graph
    static void clear(); //Deallocate edgesT's assigned memory
};
