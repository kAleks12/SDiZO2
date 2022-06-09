//
// Created by kacper on 14.05.2022.
//

#pragma once

#include <cstdlib>

struct ALElement{
    //Struct variables
    size_t vertex;
    size_t weight;
    ALElement* nextElement;

    //Struct methods
    ALElement(){
        this->vertex = SIZE_MAX;
        this->weight = SIZE_MAX;
        this->nextElement = nullptr;
    }

    ALElement(const size_t &nextVertex, const size_t &weight){
        this->vertex = nextVertex;
        this->weight = weight;
        this->nextElement = nullptr;
    }
};