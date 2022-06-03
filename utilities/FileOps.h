//
// Created by kacper on 12.05.2022.
//

#pragma once


#include <string>
#include <vector>


class FileOps {
public:
    static int* edges;
    static size_t verticesNum;
    static size_t edgesNum;
    static void readData(const std::string & fileName);

};


