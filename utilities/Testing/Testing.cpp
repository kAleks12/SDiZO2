//
// Created by kacpe on 04.06.2022.
//




#include "Testing.h"
#include "../GraphGenerator/GraphGenerator.h"

IncidencyMatrix *Testing::mGraph = nullptr;
AdjacencyList *Testing::lGraph = nullptr;


double Testing::calcAvg(const std::list<double> &dataStr) {
    double avg = 0;

    //Calculating average from provided vector's elements
    for (double result: dataStr) {
        avg += result;
    }
    avg /= double(dataStr.size());

    return avg;
}

void Testing::addSeriesAvg(double avg, size_t density, AlgorithmType alg) {
    OpResult result;

    //Creating result object for specific structure and operation
    result.time = avg;
    result.density = density;

    //Adding created object to vector with all operations' results
    switch (alg) {
        case AlgorithmType::prim:
            primResults.push_back(result);
            break;

        case AlgorithmType::kruskal:
            kruskalResults.push_back(result);
            break;

        case AlgorithmType::dijkstra:
            dijResults.push_back(result);
            break;

        case AlgorithmType::bf:
            bfResults.push_back(result);
            break;
    }
}

void Testing::calculateAlgorithmsMatrix() {
    std::list<double> pIntervals;
    std::list<double> kIntervals;
    std::list<double> dIntervals;
    std::list<double> bIntervals;
    size_t start;
    size_t finish;

    for (int verticesConf = 30; verticesConf <= 270; verticesConf += 60)
    {
        for (int density = 25; density <= 100; density += 25)
        {
            for (int i = 0; i < sampleSize; ++i)
            {
                delete mGraph;

                if (density == 100) {
                    density--;
                }

                GraphGenerator::generate(density, verticesConf, this->maxElement);
                mGraph = new IncidencyMatrix(GraphGenerator::edges, verticesConf, GraphGenerator::data);

                while (true) {
                    start = rand() % verticesConf;
                    finish = rand() % verticesConf;

                    if (start != finish) {
                        break;
                    }
                }

                watch.startCounting();

                auto result = Algorithms::primMST(mGraph);

                pIntervals.push_back(watch.getTime());

                delete result;


                watch.startCounting();

                result = Algorithms::kruskalMST(mGraph);

                kIntervals.push_back(watch.getTime());

                delete result;


                watch.startCounting();

                auto result2 = Algorithms::dijkstraPath(mGraph, start, finish);

                dIntervals.push_back(watch.getTime());

                delete result2;


                watch.startCounting();

                result2 = Algorithms::bfPath(mGraph, start, finish);

                bIntervals.push_back(watch.getTime());

                delete result2;
            }
            std::cout << "Done density -  " << density << "\n";

            addSeriesAvg(calcAvg(pIntervals), density, AlgorithmType::prim);
            addSeriesAvg(calcAvg(kIntervals), density, AlgorithmType::kruskal);
            addSeriesAvg(calcAvg(dIntervals), density, AlgorithmType::dijkstra);
            addSeriesAvg(calcAvg(bIntervals), density, AlgorithmType::bf);

            pIntervals.clear();
            kIntervals.clear();
            dIntervals.clear();
            bIntervals.clear();
        }


        saveResult("Prim", verticesConf, "matrix", AlgorithmType::prim);
        saveResult("Kruskal", verticesConf, "matrix", AlgorithmType::kruskal);
        saveResult("Dijkstra", verticesConf, "matrix", AlgorithmType::dijkstra);
        saveResult("Bellman-Ford", verticesConf, "matrix", AlgorithmType::bf);

        std::cout << "Done vertices config -  " << verticesConf << "\n\n";

        primResults.clear();
        kruskalResults.clear();
        dijResults.clear();
        bfResults.clear();
    }

}

void Testing::calculateAlgorithmsList() {
    std::list<double> pIntervals;
    std::list<double> kIntervals;
    std::list<double> dIntervals;
    std::list<double> bIntervals;
    size_t start;
    size_t finish;

    for (int verticesConf = 30; verticesConf <= 270; verticesConf += 60) {
        for (int density = 25; density <= 100; density += 25) {
            for (int i = 0; i < sampleSize; ++i) {
                delete lGraph;

                if (density == 100) {
                    density--;
                }

                GraphGenerator::generate(density, verticesConf, this->maxElement);
                lGraph = new AdjacencyList(GraphGenerator::edges, verticesConf, GraphGenerator::data);

                while (true) {
                    start = rand() % verticesConf;
                    finish = rand() % verticesConf;

                    if (start != finish) {
                        break;
                    }
                }

                watch.startCounting();

                auto result = Algorithms::primMST(lGraph);

                pIntervals.push_back(watch.getTime());

                delete result;


                watch.startCounting();

                result = Algorithms::kruskalMST(lGraph);

                kIntervals.push_back(watch.getTime());

                delete result;


                watch.startCounting();

                auto result2 = Algorithms::dijkstraPath(lGraph, start, finish);

                dIntervals.push_back(watch.getTime());

                delete result2;


                watch.startCounting();

                result2 = Algorithms::bfPath(lGraph, start, finish);

                bIntervals.push_back(watch.getTime());

                delete result2;
            }
            std::cout << "Done density -  " << density << "\n";

            addSeriesAvg(calcAvg(pIntervals), density, AlgorithmType::prim);
            addSeriesAvg(calcAvg(kIntervals), density, AlgorithmType::kruskal);
            addSeriesAvg(calcAvg(dIntervals), density, AlgorithmType::dijkstra);
            addSeriesAvg(calcAvg(bIntervals), density, AlgorithmType::bf);

            pIntervals.clear();
            kIntervals.clear();
            dIntervals.clear();
            bIntervals.clear();
        }


        saveResult("Prim", verticesConf, "list", AlgorithmType::prim);
        saveResult("Kruskal", verticesConf, "list", AlgorithmType::kruskal);
        saveResult("Dijkstra", verticesConf, "list", AlgorithmType::dijkstra);
        saveResult("Bellman-Ford", verticesConf, "list", AlgorithmType::bf);

        std::cout << "Done vertices config -  " << verticesConf << "\n\n";

        primResults.clear();
        kruskalResults.clear();
        dijResults.clear();
        bfResults.clear();
    }

}

void Testing::saveResult(const std::string &algorithm, size_t verticesNum, const std::string &representation, AlgorithmType alg) {
    //Creating write file
    std::ofstream saveFile(algorithm + "//" + representation + "//test - " + std::to_string(verticesNum) + ".txt");

    auto results = primResults;

    switch (alg) {
        case AlgorithmType::prim:
            results = primResults;
            break;

        case AlgorithmType::kruskal:
            results = kruskalResults;
            break;

        case AlgorithmType::dijkstra:
            results = dijResults;
            break;

        case AlgorithmType::bf:
            results = bfResults;
            break;
    }

    //Printing opResult objects for each tested operation to the file
    for (const OpResult &result: results) {
        saveFile << result.density << ";" << result.time << "\n";
    }

    saveFile.close();
}