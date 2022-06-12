//
// Created by kacper on 12.05.2022.
//

#include <fstream>
#include <iostream>
#include "FileOps.hpp"
#include <vector>

int* FileOps::edges = nullptr;
size_t FileOps::verticesNum = -1;
size_t FileOps::edgesNum = -1;

void FileOps::readData(const std::string &fileName) {
    delete [] edges;
    //Opening source file
    std::ifstream srcFile(fileName);

    //Checking whether file exists
    if (!srcFile.is_open()) {
        std::cout << "File not found\n\n";
        return ;
    }

    srcFile >> FileOps::edgesNum;
    srcFile >> FileOps::verticesNum;

    FileOps::edges = new int[edgesNum*3];
    std::string tmp;

    //Filling the array with data from source file
    for (int i = 0; i < FileOps::edgesNum * 3; i++) {
        srcFile >> tmp;
        edges[i] = std::stoi(tmp);
    }

    srcFile.close();
}