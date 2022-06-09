#pragma once

class GraphGenerator {

public:
    static size_t* data;
    static size_t edges;

    static void generate(size_t density, size_t nodeNumber, size_t maxValue);
};
