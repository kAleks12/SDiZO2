//
// Created by kacper on 01.06.2022.
//
#pragma once

#include <iostream>

//Structure used to make output path in SP algorithms
struct PElement {
    size_t cost;
    size_t previousV;
    size_t nextV;

    PElement(size_t cost, size_t previousV, size_t nextV): cost(cost), previousV(previousV), nextV(nextV)
    {}

    PElement() : cost(0), previousV(0), nextV(0)
    {}


    friend bool operator==(PElement const &first, PElement const &second) {
        return first.cost == second.cost;
    }

    friend std::ostream& operator<<(std::ostream& os, const PElement &element) {
        os << "->" << element.previousV << " -> " << element.nextV << " ( " << element.cost << ")";
        return os;
    }

    std::string toString(){
        std::string str =  " -> " + std::to_string(nextV) + " ("  + std::to_string(cost) + ")";
        return str;
    }
};