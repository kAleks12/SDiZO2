//
// Created by kacpe on 04.06.2022.
//

#pragma once

#include <cstdlib>
#include <list>
#include "../TimeMeasurement.hpp"
#include "../../algorithms/Algorithms.hpp"

//Helping structure for individual results
struct OpResult {
    double time;
    size_t density;
};


class Testing {
    public:
        //Class variables
        static IncidencyMatrix* mGraph;
        static AdjacencyList* lGraph;

        size_t sampleSize = 20;
        int maxElement = 100;
        TimeMeasurement watch;
        std::list<OpResult> primResults;
        std::list<OpResult> kruskalResults;
        std::list<OpResult> dijResults;
        std::list<OpResult> bfResults;

        //Class methods
        static double calcAvg(const std::list<double> &); //Calculate average time from list elements
        void addSeriesAvg(double avg, size_t density, AlgorithmType alg); //Add avg time to adequate result list

        void calculateAlgorithmsMatrix(); //Perform testing for all algorithms in matrix representation
        void calculateAlgorithmsList(); //Perform testing for all algorithms in list representation

        void saveResult(const std::string &algorithm, size_t verticesNum, const std::string& representation, AlgorithmType alg); //Save results an algorithm to file
};

