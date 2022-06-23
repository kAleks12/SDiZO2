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

    mkdir("Kruskal");
    mkdir("Kruskal//matrix");
    mkdir("Kruskal//list");

    mkdir("Dijkstra");
    mkdir("Dijkstra//matrix");
    mkdir("Dijkstra//list");

    mkdir("Bellman-Ford");
    mkdir("Bellman-Ford//matrix");
    mkdir("Bellman-Ford//list");

    tests.calculateAlgorithmsMatrix();
    tests.calculateAlgorithmsList();


    //UI::startMenu();
}