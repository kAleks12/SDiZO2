#pragma once

#include <cstdlib>
#include <list>
#include "../TimeMeasurement.h"
#include "../../algorithms/Algorithms.h"

struct OperationResultData {
    double time;
    size_t density;
};


class Simulation {
    public:
        static MatrixGraph* mGraph;
        static ListGraph* lGraph;

        size_t sampleSize = 20;
        int maxElementValue = 100;
        TimeMeasurement watch;
        std::list<OperationResultData> primResults;
        std::list<OperationResultData> kruskalResults;
        std::list<OperationResultData> dijResults;
        std::list<OperationResultData> bfResults;

        static double calcAvg(const std::list<double> &);
        void addSeriesAvg(double avg, size_t density, AlgorithmType alg);

        void calculateAlgorithmsMatrix();
        void calculateAlgorithmsList();

        void saveResult(const std::string &algorithm, size_t verticesNum, const std::string& representation, AlgorithmType alg);
};

