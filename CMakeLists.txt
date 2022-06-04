cmake_minimum_required(VERSION 3.21)
project(SDiZO_2)


set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(
        SDiZO_2
        main.cpp

        containers/DynamicArray/DynamicArray.hpp
        containers/DynamicArray/DynamicArray.tpp

        containers/EdgeHeap/Edge.h
        containers/AdjacencyList/ALElement.h
        containers/IncidencyMatrix/MatrixCell.h

        containers/AdjacencyList/AdjacencyList.h
        containers/AdjacencyList/AdjacencyList.cpp
        containers/IncidencyMatrix/IncidencyMatrix.cpp
        containers/IncidencyMatrix/IncidencyMatrix.h
        containers/EdgeHeap/EdgeHeap.cpp
        containers/EdgeHeap/EdgeHeap.h

        algorithms/Algorithms.cpp
        algorithms/Algorithms.h
        utilities/PathElement.h
        utilities/Results.h

        utilities/Enums.h
        utilities/FileOps/FileOps.h
        utilities/FileOps/FileOps.cpp
        utilities/GraphGenerator/GraphGenerator.cpp
        utilities/GraphGenerator/GraphGenerator.h
        utilities/TimeMeasurement.hpp

        utilities/Testing/Testing.cpp
        utilities/Testing/Testing.h

        UI/UI.cpp
        UI/UI.h
)
