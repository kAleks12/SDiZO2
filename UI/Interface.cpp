#include <string>
#include <iostream>
#include <windows.h>
#include <ctime>
#include "Interface.h"
#include "../utilities/FileOps/FileManagement.h"
#include "../algorithms/Algorithms.h"
#include "../utilities/GraphGenerator/GraphGenerator.h"

MatrixGraph *Interface::mGraph = nullptr;
ListGraph *Interface::lGraph = nullptr;

//Initial interface menu
void Interface::startMenu() {
    std::string choice;

    while (true) {
        system("cls");
        std::cout << "[0] MST\n";
        std::cout << "[1] Shortest path\n";
        std::cout << "[Q] Quit\n";
        std::cout << "Input choice: ";
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
        Sleep(2000);
        system("cls");
    }
}

//Interface submenu for MST problem
void Interface::MSTSubMenu() {
    std::string choice;
    while (true) {
        system("cls");

        std::cout << "[0] File input\n";
        std::cout << "[1] Random graph\n";
        std::cout << "[2] Show\n";
        std::cout << "[3] Prim\n";
        std::cout << "[4] Kruskal\n";
        std::cout << "[Q] Quit\n";
        std::cout << "\nInput choice: ";
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
            doPrim();
            continue;
        }

        if (choice == "4") {
            system("cls");
            doKruskal();
            continue;
        }

        if (choice == "q" || choice == "Q") {
            return;
        }

        std::cout << "Invalid input!";
        Sleep(2000);
        system("cls");
    }
}

//Interface submenu for SP problem
void Interface::SPSubMenu() {
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
            auto spPair = getShortestPathMode();

            system("cls");
            doDijkstra(spPair[0], spPair[1]);
            continue;
        }

        if (choice == "4") {
            system("cls");
            auto spPair = getShortestPathMode();

            system("cls");
            doBelmanFord(spPair[0], spPair[1]);
            continue;
        }

        if (choice == "q" || choice == "Q") {
            return;
        }

        std::cout << "Invalid input!";
        Sleep(2000);
        system("cls");
    }
}


//Interface menu for creating a graph from file data
void Interface::fileGraph() {

    delete Interface::mGraph;
    delete Interface::lGraph;

    std::string filename;
    std::cout << "Enter name of the file: ";
    std::cin >> filename;

    FileManagement::readData(filename);

    if (FileManagement::edges == nullptr) {
        std::cout << "There is no such file!";
        Sleep(2000);
        system("cls");
        return;
    }
    Interface::mGraph = new MatrixGraph();
    Interface::lGraph = new ListGraph();

    std::cout << "\n\nGraph created from file " + filename + "\n";
    Sleep(2000);
}

//Interface menu for creating random graph with GraphGenerator
void Interface::randomGraph() {
    delete Interface::mGraph;
    delete Interface::lGraph;

    size_t nodesNumber;
    size_t density;

    std::string input;

    while (true) {
        system("cls");
        std::cout << "Enter number of nodes: ";
        std::cin >> input;

        try {
            nodesNumber = std::stoi(input);
            break;
        }
        catch (std::exception &e) {
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
        catch (std::exception &e) {
            std::cout << "NaN";
            Sleep(2000);
        }
    }

    GraphGenerator::generate(density, nodesNumber, 15);

    Interface::mGraph = new MatrixGraph(GraphGenerator::edges, nodesNumber, GraphGenerator::data);
    Interface::lGraph = new ListGraph(GraphGenerator::edges, nodesNumber, GraphGenerator::data);

    std::cout << "\n\nCreated random graph\n";
    Sleep(2000);
}

//Display both representations of currently loaded graph
void Interface::displayGraphs() {
    std::cout << " Matrix representation:\n";
    Interface::mGraph->print();

    std::cout << "\n\nList representation:\n";
    Interface::lGraph->print();

    std::cout << "\n";
    system("Pause");
}


//Execute prim algorithm for current graph and display results
void Interface::doPrim() {
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
void Interface::doKruskal() {
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
void Interface::doDijkstra(size_t start, size_t finish) {
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

    } catch (std::out_of_range &e) {

        std::cout << "One of nodes is out ouf bound!";
        Sleep(2000);
        return;
    }
}

//Execute bellman-ford algorithm for current graph and display results
void Interface::doBelmanFord(size_t start, size_t finish) {
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

    } catch (std::out_of_range &e) {
        std::cout << "One of nodes is out ouf bound!";
        Sleep(2000);
        return;
    }
}

//Interface menu for selecting start and finish nodes for SP algorithms
std::vector<size_t> Interface::getShortestPathMode() {
    srand(time(nullptr));
    std::string input;
    std::vector<size_t> nodes;

    while (true) {
        system("cls");

        std::cout << "[0] Choose nodes pair randomly\n";
        std::cout << "[1] Choose nodes pair manually\n";
        std::cout << "\nInput: ";

        std::cin >> input;

        if (input == "0" || input == "1") {
            break;
        }
    }

    if (input == "0") {
        while (true) {
            nodes.push_back(rand() % (Interface::mGraph->getNodesNumber()));
            nodes.push_back(rand() % (Interface::mGraph->getNodesNumber()));

            if (nodes[0] != nodes[1]) {
                break;
            }

            nodes.clear();
        }
    } else {
        while (true) {
            system("cls");

            std::cout << "Enter start node: ";
            std::cin >> input;

            if (std::stoi(input) < 0 && std::stoi(input) > mGraph->getNodesNumber()) {
                continue;
            }

            nodes.push_back(std::stoi(input));
            break;
        }

        while (true) {
            system("cls");

            std::cout << "Enter finish node: ";
            std::cin >> input;

            if (std::stoi(input) < 0 && std::stoi(input) > mGraph->getNodesNumber()) {
                nodes.clear();
                continue;
            }

            nodes.push_back(std::stoi(input));
            break;
        }
    }

    return nodes;
}