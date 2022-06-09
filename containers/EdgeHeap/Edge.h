//
// Created by kacper on 14.05.2022.
//

#pragma once

#include <cstdlib>

struct Edge{
    //Struct variables
    size_t origin;
    size_t destination;
    size_t weight;

    //Default constructor
    Edge(){
        this->origin = -1;
        this->destination = -1;
        this->weight = -1;
    }

    //Normal constructor
    Edge(const size_t &originVertex, const size_t &destVertex, const size_t &weight){
        this->origin = originVertex;
        this->destination = destVertex;
        this->weight = weight;
    }

    //Overload of < operator
    bool operator < ( const Edge & edge ) const
    {
        if( this->weight < edge.weight )
            return true;
        else
            return false;
    }

    //Overload of > operator
    bool operator > ( const Edge & edge ) const
    {
        if( this->weight > edge.weight )
            return true;
        else
            return false;
    }

};
