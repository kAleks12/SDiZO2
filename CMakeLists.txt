cmake_minimum_required(VERSION 3.21)
project(SDiZO_2)


set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(
        SDiZO_2
        main.cpp
        containers/NeighbourhoodList/NeighbourhoodList.h
        containers/NeighbourhoodList/NeighbourhoodList.cpp
        utilities/Edge.h
        containers/AdjacencyMatrix/AdjacencyMatrix.cpp containers/AdjacencyMatrix/AdjacencyMatrix.h utilities/NListElement.h utilities/MatrixCell.h utilities/Enums.h)
