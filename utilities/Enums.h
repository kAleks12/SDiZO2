//
// Created by kacpe on 14.05.2022.
//

#pragma once

enum class CellType{
    loop = 2,
    origin = 1,
    destination = -1,
    empty = 0
};

enum class AlgorithmType{
    prim = 0,
    kruskal = 1,
    dijkstra = 2,
    bf = 3
};
