#pragma once

#include <cstdlib>
#include "../../utilities/Enums.h"

struct MatrixElement{
    TypeOfCell type;
    size_t weight;

    MatrixElement(): type{TypeOfCell::empty}, weight{0}
    {}

    MatrixElement(TypeOfCell type, const size_t &weight): type{type}, weight{weight}
    {}
};