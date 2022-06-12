//
// Created by kacper on 03.06.2022.
//

#include <string>
#include <iostream>
#include <windows.h>
#include "UI.hpp"
#include "../utilities/FileOps/FileOps.hpp"
#include "../algorithms/Algorithms.hpp"
#include "../utilities/GraphGenerator/GraphGenerator.hpp"

IncidencyMatrix *UI::mGraph = nullptr;
AdjacencyList *UI::lGraph = nullptr;

//Initial interface menu
void UI::startMenu() {
    std::string choice;

    while (true) {
        system("cls");
        std::cout << "[0] MST\n";
        std::cout << "[1] Shortest path\n";
        std::cout << "[Q] Quit\n";
        std::cout << "Hello, choose problem: ";
        std::cin >> choice;

        if (choice == "0") {
            system("cls");
            MSTSubMenu();
            continue;
        }

        if (choice == "1") {
            system("cls");
            SPSubMenu();
            continue;
        }

        if (choice == "q" || choice == "Q") {
            return;
        }

        std::cout << "Invalid input!";
        Sleep(1000);
        system("cls");
    }
}

//Interface submenu for MST problem
void UI::MSTSubMenu() {
    std::string choice;
    while (true) {
        system("cls");

        std::cout << "[0] Create graph from file\n";
        std::cout << "[1] Generate random graph\n";
        std::cout << "[2] Display current graph\n";
        std::cout << "[3] Prim\n";
        std::cout << "[4] Kruskal\n";
        std::cout << "[Q] Quit\n";
        std::cout << "\nHello, choose algorithm: ";
        std::cin >> choice;

        if (choice == "0") {
            system("cls");
            fileGraph();
            continue;
        }

        if (choice == "1") {
            system("cls");
            randomGraph();
            continue;
        }

        if (choice == "2") {
            system("cls");
            displayGraphs();
            continue;
        }

        if (choice == "3") {
            system("cls");
            performPrim();
            continue;
        }

        if (choice == "4") {
            system("cls");
            performKruskal();
            continue;
        }

        if (choice == "q" || choice == "Q") {
            return;
        }

        std::cout << "Invalid input!";
        Sleep(1000);
        system("cls");
    }
}

//Interface submenu for SP problem
void UI::SPSubMenu() {
    std::string choice;
    while (true) {
        system("cls");

        std::cout << "[0] Create graph from file\n";
        std::cout << "[1] Generate random graph\n";
        std::cout << "[2] Display current graph\n";
        std::cout << "[3] Dijkstra\n";
        std::cout << "[4] Bellman-Ford\n";
        std::cout << "[Q] Quit\n";
        std::cout << "\nHello, choose algorithm: ";
        std::cin >> choice;

        if (choice == "0") {
            system("cls");
            fileGraph();
            continue;
        }

        if (choice == "1") {
            system("cls");
            randomGraph();
            continue;
        }

        if (choice == "2") {
            system("cls");
            displayGraphs();
            continue;
        }

        if (choice == "3") {
            system("cls");
            auto spPair = getSPMode();

            system("cls");
            performDijkstra(spPair[0], spPair[1]);
            continue;
        }

        if (choice == "4") {
            system("cls");
            auto spPair = getSPMode();

            system("cls");
            performBF(spPair[0], spPair[1]);
            continue;
        }

        if (choice == "q" || choice == "Q") {
            return;
        }

        std::cout << "Invalid input!";
        Sleep(1000);
        system("cls");
    }
}


//Interface menu for creating a graph from file data
void UI::fileGraph() {

    delete UI::mGraph;
    delete UI::lGraph;

    std::string filename;
    std::cout << "Enter name of the file: ";
    std::cin >> filename;

    FileOps::readData(filename);

    if (FileOps::edges == nullptr) {
        std::cout << "There is no such file!";
        Sleep(2000);
        system("cls");
        return;
    }
    UI::mGraph = new IncidencyMatrix();
    UI::lGraph = new AdjacencyList();

    std::cout << "\n\nGraph created from file " + filename + "\n";
    Sleep(2000);
}

//Interface menu for creating random graph with GraphGenerator
void UI::randomGraph() {
    delete UI::mGraph;
    delete UI::lGraph;

    size_t verNum;
    size_t density;

    std::string input;

    while (true) {
        system("cls");
        std::cout << "Enter number of vertices: ";
        std::cin >> input;

        try {
            verNum = std::stoi(input);
            break;
        }
        catch (std::exception& e) {
            std::cout << "NaN";
            Sleep(2000);
        }
    }

    while (true) {
        system("cls");
        std::cout << "Enter density | (0-100] [%] |: ";
        std::cin >> input;

        try {
            density = std::stoi(input);

            if (density > 0 && density <= 100) {
                break;
            }
        }
        catch (std::exception& e) {
            std::cout << "NaN";
            Sleep(2000);
        }
    }

    GraphGenerator::generate(density, verNum, 15);

    UI::mGraph = new IncidencyMatrix(GraphGenerator::edges, verNum, GraphGenerator::data);
    UI::lGraph = new AdjacencyList(GraphGenerator::edges, verNum, GraphGenerator::data);

    std::cout << "\n\nCreated random graph\n";
    Sleep(2000);
}

//Display both representations of currently loaded graph
void UI::displayGraphs() {
    std::cout << " Matrix representation:\n";
    UI::mGraph->print();

    std::cout << "\n\nList representation:\n";
    UI::lGraph->print();

    std::cout << "\n";
    system("Pause");
}


//Execute prim algorithm for current graph and display results
void UI::performPrim() {
    Algorithms::primMST(mGraph);
    auto result2 = Algorithms::primMST(lGraph);
    auto result = Algorithms::primMST(mGraph);

    std::cout << "Prim [matrix]:\n\n";
    result->display();

    std::cout << "\n\n\nPrim [list]:\n\n";
    result2->display();

    delete result2;

    std::cout << "\n\n";
    system("Pause");
}

//Execute kruskal algorithm for current graph and display results
void UI::performKruskal() {
    auto result = Algorithms::kruskalMST(mGraph);
    auto result2 = Algorithms::kruskalMST(lGraph);

    std::cout << "Kruskal [matrix]:\n\n";
    result->display();
    std::cout << "\n\n\nKruskal [list]:\n\n";
    result2->display();

    delete result;
    delete result2;

    std::cout << "\n\n";
    system("Pause");
}


//Execute dijkstra algorithm for current graph and display results
void UI::performDijkstra(size_t start, size_t finish) {
    try {
        auto result = Algorithms::dijkstraPath(mGraph, start, finish);
        auto result2 = Algorithms::dijkstraPath(lGraph, start, finish);

        std::cout << "Dijkstra [matrix] path - (" << start << "," << finish << "):\n\n";
        result->display();
        std::cout << "\n\n\nDijkstra [list] path - (" << start << "," << finish << "):\n\n";
        result2->display();

        delete result;
        delete result2;

        std::cout << "\n\n";
        system("Pause");

    }catch(std::out_of_range& e){

        std::cout << "At least one of vertices was out ouf bound!";
        Sleep(3000);
        return;
    }
}

//Execute bellman-ford algorithm for current graph and display results
void UI::performBF(size_t start, size_t finish) {
    try {
        auto result = Algorithms::bfPath(mGraph, start, finish);
        auto result2 = Algorithms::bfPath(lGraph, start, finish);

        std::cout << "Bellman-Ford [matrix] path - (" << start << "," << finish << "):\n\n";
        result->display();
        std::cout << "\n\n\nBellman-Ford [list] path - (" << start << "," << finish << "):\n\n";
        result2->display();

        delete result;
        delete result2;

        std::cout << "\n\n";
        system("Pause");

    }catch(std::out_of_range& e){
        std::cout << "At least one of vertices was out ouf bound!";
        Sleep(3000);
        return;
    }
}


//Interface menu for selecting start and finish vertices for SP algorithms
std::vector<size_t> UI::getSPMode() {
    srand(time(nullptr));
    std::string input;
    std::vector<size_t> vertices;

    while (true) {
        system("cls");

        std::cout << "[0] Choose vertices pair randomly\n";
        std::cout << "[1] Choose vertices pair manually\n";
        std::cout << "\nInput: ";

        std::cin >> input;

        if (input == "0" || input == "1") {
            break;
        }
    }

    if (input == "0") {
        while (true) {
            vertices.push_back(rand() % (UI::mGraph->getVerticesNumber()));
            vertices.push_back(rand() % (UI::mGraph->getVerticesNumber()));

            if (vertices[0] != vertices[1]) {
                break;
            }

            vertices.clear();
        }
    } else {
        while (true) {
            system("cls");

            std::cout << "Enter start vertex: ";
            std::cin >> input;

            if (std::stoi(input) < 0 && std::stoi(input) > mGraph->getVerticesNumber()) {
                continue;
            }

            vertices.push_back(std::stoi(input));
            break;
        }

        while (true) {
            system("cls");

            std::cout << "Enter finish vertex: ";
            std::cin >> input;

            if (std::stoi(input) < 0 && std::stoi(input) > mGraph->getVerticesNumber()) {
                vertices.clear();
                continue;
            }

            vertices.push_back(std::stoi(input));
            break;
        }
    }

    return vertices;
}