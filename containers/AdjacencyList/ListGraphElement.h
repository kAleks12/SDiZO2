#pragma once

#include <cstdlib>

struct ListGraphElement{
    size_t node;
    size_t weight;
    ListGraphElement* nextElement;

    ListGraphElement(){
        this->node = SIZE_MAX;
        this->weight = SIZE_MAX;
        this->nextElement = nullptr;
    }

    ListGraphElement(const size_t &nextNode, const size_t &weight){
        this->node = nextNode;
        this->weight = weight;
        this->nextElement = nullptr;
    }
};