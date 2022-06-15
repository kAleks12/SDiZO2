#pragma once

//Types of matrix cells for Incidency Matrix
enum class TypeOfCell{
    loop = 2,
    origin = 1,
    destination = -1,
    empty = 0
};

//Types of algorithms
enum class AlgorithmName{
    prim = 0,
    kruskal = 1,
    dijkstra = 2,
    bf = 3
};
