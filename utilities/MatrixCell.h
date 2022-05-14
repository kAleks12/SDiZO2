//
// Created by kacpe on 14.05.2022.
//

#pragma once

#include <cstdlib>
#include "Enums.h"

struct MatrixCell{
    CellType type;
    size_t weight;

    MatrixCell(): type{CellType::empty}, weight{0}
    {}
    MatrixCell(CellType type, const size_t &weight): type{type}, weight{weight}
    {};
};