#pragma once

#include <cstdlib>

struct ListGraphElement{
    size_t vertex;
    size_t weight;
    ListGraphElement* nextElement;

    ListGraphElement(){
        this->vertex = SIZE_MAX;
        this->weight = SIZE_MAX;
        this->nextElement = nullptr;
    }

    ListGraphElement(const size_t &nextVertex, const size_t &weight){
        this->vertex = nextVertex;
        this->weight = weight;
        this->nextElement = nullptr;
    }
};