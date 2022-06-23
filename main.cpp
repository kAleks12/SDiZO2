//
// Created by kacper on 14.05.2022.
//


#include <sys/stat.h>
#include "UI/UI.hpp"
#include "algorithms/Algorithms.hpp"
#include "utilities/Testing/Testing.hpp"

int main() {

    Testing tests;

    mkdir("Prim");
    mkdir("Prim//matrix");
    mkdir("Prim//list");


    //tests.calculateAlgorithmsMatrix();
    tests.calculateAlgorithmsList();


    //UI::startMenu();
}