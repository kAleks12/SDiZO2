#pragma once


#include <string>
#include <vector>


class FileManagement {
public:
    static int* edges;
    static size_t verticesNum;
    static size_t edgesNum;
    static void readData(const std::string & fileName);

};


