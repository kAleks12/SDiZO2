//
// Created by kacpe on 04.06.2022.
//

#pragma once

#include <cstdlib>
#include <list>
#include "TimeMeasurement.hpp"
#include "../../algorithms/Algorithms.h"

struct OpResult {
    double time;
    size_t density;
};


class Testing {
    public:
        static IncidencyMatrix* mGraph;
        static AdjacencyList* lGraph;

        size_t sampleSize = 20;
        int maxElement = 100;
        TimeMeasurement watch;
        std::list<OpResult> results;

        static double calcAvg(const std::list<double> &);

        void addSeriesAvg(double avg, size_t density);

        void calculateAlgorithmMatrix(AlgorithmType algorithm);

        void calculateAlgorithmList(AlgorithmType algorithm);

        void saveResult(const std::string &algorithm, size_t verticesNum, const std::string& representation);
};

