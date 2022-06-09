//
// Created by kacper on 01.06.2022.
//
#pragma once

#include <iostream>

//Structure used to make output path in SP algorithms
struct PElement {
    //Struct variables
    size_t cost;
    size_t previousV;
    size_t nextV;

    //Struct methods
    PElement(size_t cost, size_t previousV, size_t nextV): cost(cost), previousV(previousV), nextV(nextV)
    {} //Constructor

    PElement() : cost(0), previousV(0), nextV(0)
    {} //Default constructor

    //Overload for operator ==
    friend bool operator==(PElement const &first, PElement const &second) {
        return first.cost == second.cost;
    }

    //Overload for operator <<
    friend std::ostream& operator<<(std::ostream& os, const PElement &element) {
        os << "->" << element.previousV << " -> " << element.nextV << " ( " << element.cost << ")";
        return os;
    }

    //Function that returns string representing path
    std::string toString() const{
        std::string str =  " -> " + std::to_string(nextV) + " ("  + std::to_string(cost) + ")";
        return str;
    }
};