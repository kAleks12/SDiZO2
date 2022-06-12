cmake_minimum_required(VERSION 3.21)
project(SDiZO_2)


set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(
        SDiZO_2
        main.cpp

        containers/DynamicArray/DynamicArray.hpp
        containers/DynamicArray/DynamicArray.tpp

        containers/EdgeHeap/Edge.hpp
        containers/AdjacencyList/ALElement.hpp
        containers/IncidencyMatrix/MatrixCell.hpp

        containers/AdjacencyList/AdjacencyList.hpp
        containers/AdjacencyList/AdjacencyList.cpp
        containers/IncidencyMatrix/IncidencyMatrix.cpp
        containers/IncidencyMatrix/IncidencyMatrix.hpp
        containers/EdgeHeap/EdgeHeap.cpp
        containers/EdgeHeap/EdgeHeap.hpp

        algorithms/Algorithms.cpp
        algorithms/Algorithms.hpp
        utilities/PathElement.hpp
        utilities/Results.hpp

        utilities/Enums.hpp
        utilities/FileOps/FileOps.hpp
        utilities/FileOps/FileOps.cpp
        utilities/GraphGenerator/GraphGenerator.cpp
        utilities/GraphGenerator/GraphGenerator.hpp
        utilities/TimeMeasurement.hpp

        utilities/Testing/Testing.cpp
        utilities/Testing/Testing.hpp

        UI/UI.cpp
        UI/UI.hpp
)
