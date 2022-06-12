//
// Created by kacper on 12.05.2022.
//

#pragma once


#include <string>
#include <vector>
#include <list>
#include "../Testing/Testing.hpp"


class FileOps {
public:
    //Class variables
    static int* edges;
    static size_t verticesNum;
    static size_t edgesNum;

    //Class methods
    static void readData(const std::string & fileName); //read graph from file 'fileName'
    static void saveData(const std::string &fileName, const std::list<OpResult> &data);

};


