//
// Created by kacper on 14.05.2022.
//

#pragma once

#include <cstdlib>

struct Edge{
    size_t origin;
    size_t destination;
    size_t weight;

    Edge(const size_t &originVertex, const size_t &destVertex, const size_t &weight){
        this->origin = originVertex;
        this->destination = destVertex;
        this->weight = weight;
    }
};
