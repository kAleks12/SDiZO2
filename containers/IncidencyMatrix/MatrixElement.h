#pragma once

#include <cstdlib>
#include "../../utilities/Enums.h"

struct MatrixElement{
    CellType type;
    size_t weight;

    MatrixElement(): type{CellType::empty}, weight{0}
    {}

    MatrixElement(CellType type, const size_t &weight): type{type}, weight{weight}
    {}
};