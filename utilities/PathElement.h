#pragma once

#include <iostream>

//Structure used to make output path in SP algorithms
struct PElement {
    size_t cost;
    size_t previousNode;
    size_t nextNode;

    PElement(size_t cost, size_t previousV, size_t nextV) : cost(cost), previousNode(previousV), nextNode(nextV) {}

    PElement() : cost(0), previousNode(0), nextNode(0) {}


    friend bool operator==(PElement const &first, PElement const &second) {
        return first.cost == second.cost;
    }

    friend std::ostream &operator<<(std::ostream &os, const PElement &element) {
        os << "->" << element.previousNode << " -> " << element.nextNode << " ( " << element.cost << ")";
        return os;
    }

    std::string toString() {
        std::string str = " -> " + std::to_string(nextNode) + " (" + std::to_string(cost) + ")";
        return str;
    }
};