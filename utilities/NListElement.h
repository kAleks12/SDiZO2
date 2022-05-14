//
// Created by kacpe on 14.05.2022.
//

#pragma once

#include <cstdlib>

struct NListElement{
    size_t vertex;
    size_t weight;
    NListElement* nextElement;

    NListElement(){
        this->vertex = SIZE_MAX;
        this->weight = SIZE_MAX;
        this->nextElement = nullptr;
    }

    NListElement(const size_t &nextVertex, const size_t &weight){
        this->vertex = nextVertex;
        this->weight = weight;
        this->nextElement = nullptr;
    }
};