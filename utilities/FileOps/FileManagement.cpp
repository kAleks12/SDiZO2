#include <fstream>
#include <iostream>
#include "FileManagement.h"
#include <vector>

int* FileManagement::edges = nullptr;
size_t FileManagement::verticesNum = -1;
size_t FileManagement::edgesNum = -1;

void FileManagement::readData(const std::string &fileName) {
    delete [] edges;
    //Opening source file
    std::ifstream srcFile(fileName);

    //Checking whether file exists
    if (!srcFile.is_open()) {
        std::cout << "File not found\n\n";
        return ;
    }

    srcFile >> FileManagement::edgesNum;
    srcFile >> FileManagement::verticesNum;

    FileManagement::edges = new int[edgesNum * 3];
    std::string tmp;

    //Filling the array with data from source file
    for (int i = 0; i < FileManagement::edgesNum * 3; i++) {
        srcFile >> tmp;
        edges[i] = std::stoi(tmp);
    }

    srcFile.close();
}