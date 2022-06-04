//
// Created by kacper on 03.06.2022.
//

#pragma once

class GraphGenerator {

public:
    static size_t* data;
    static size_t edges;

    static void generate(size_t density, size_t vertexNumber, size_t maxValue);
};
