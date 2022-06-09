#pragma once

#include <cstdlib>
#include <list>
#include "../TimeMeasurement.h"
#include "../../algorithms/Algorithms.h"

struct OpResult {
    double time;
    size_t density;
};


class Testing {
    public:
        static MatrixGraph* mGraph;
        static ListGraph* lGraph;

        size_t sampleSize = 20;
        int maxElement = 100;
        TimeMeasurement watch;
        std::list<OpResult> primResults;
        std::list<OpResult> kruskalResults;
        std::list<OpResult> dijResults;
        std::list<OpResult> bfResults;

        static double calcAvg(const std::list<double> &);
        void addSeriesAvg(double avg, size_t density, AlgorithmType alg);

        void calculateAlgorithmsMatrix();
        void calculateAlgorithmsList();

        void saveResult(const std::string &algorithm, size_t verticesNum, const std::string& representation, AlgorithmType alg);
};

