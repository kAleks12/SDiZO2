//
// Created by kacpe on 14.05.2022.
//

#pragma once

#include <cstdlib>
#include "../../utilities/Enums.hpp"

struct MatrixCell{
    //Struct variables
    CellType type;
    size_t weight;

    //Class methods
    MatrixCell(): type{CellType::empty}, weight{0}
    {} //Default constructor

    MatrixCell(CellType type, const size_t &weight): type{type}, weight{weight}
    {} //Normal constructor
};