cmake_minimum_required(VERSION 3.21)
cmake_minimum_required(VERSION 3.21)
project(SDiZO_2)


set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(
        SDiZO_2
        main.cpp

        containers/DynamicArray/MyArray.h
        containers/DynamicArray/MyArray.tpp

        containers/EdgeHeap/Edge.h
        containers/AdjacencyList/ListGraphElement.h
        containers/IncidencyMatrix/MatrixElement.h

        containers/AdjacencyList/ListGraph.h
        containers/AdjacencyList/ListGraph.cpp
        containers/IncidencyMatrix/MatrixGraph.cpp
        containers/IncidencyMatrix/MatrixGraph.h
        containers/EdgeHeap/MyHeap.cpp
        containers/EdgeHeap/MyHeap.h

        algorithms/Algorithms.cpp
        algorithms/Algorithms.h
        utilities/PathElement.h
        utilities/Results.h

        utilities/Enums.h
        utilities/FileOps/FileManagement.h
        utilities/FileOps/FileManagement.cpp
        utilities/GraphGenerator/GraphGenerator.cpp
        utilities/GraphGenerator/GraphGenerator.h
        utilities/TimeMeasurement.h

        utilities/Testing/Testing.cpp
        utilities/Testing/Testing.h

        UI/Interface.cpp
        UI/Interface.h
)
