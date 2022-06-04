//
// Created by kacper on 14.05.2022.
//

#pragma once

#include <cstdlib>

struct ALElement{
    size_t vertex;
    size_t weight;
    ALElement* nextElement;

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