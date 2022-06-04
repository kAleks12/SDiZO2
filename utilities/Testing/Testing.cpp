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

void Testing::addSeriesAvg(double avg, size_t density) {
    OpResult result;

    //Creating result object for specific structure and operation
    result.time = avg;
    result.density = density;

    //Adding created object to vector with all operations' results
    results.push_back(result);
}

void Testing::calculateAlgorithmMatrix(AlgorithmType algorithm)
{
    std::list <double> intervals;
    size_t start;
    size_t finish;

    for(int verticesConf = 30; verticesConf <= 270; verticesConf += 60) {
        for (int density = 25; density <= 100; density += 25)
        {
            for (int i = 0; i < sampleSize; ++i) {
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


                if (algorithm == AlgorithmType::prim) {
                    watch.startCounting();

                    auto result = Algorithms::primMST(mGraph);

                    intervals.push_back(watch.getTime());

                    delete result;
                }

                if (algorithm == AlgorithmType::kruskal) {
                    watch.startCounting();

                    auto result = Algorithms::kruskalMST(mGraph);

                    intervals.push_back(watch.getTime());

                    delete result;
                }

                if (algorithm == AlgorithmType::dijkstra) {
                    watch.startCounting();


                    auto result = Algorithms::dijkstraPath(mGraph, start, finish);

                    intervals.push_back(watch.getTime());

                    delete result;
                }

                if (algorithm == AlgorithmType::bf) {
                    watch.startCounting();

                    auto result = Algorithms::bfPath(mGraph, start, finish);

                    intervals.push_back(watch.getTime());

                    delete result;
                }

            }
            std::cout << "Done density -  " << density << "\n";
            addSeriesAvg(calcAvg(intervals), density);
            intervals.clear();
        }

        switch (algorithm) {
            case AlgorithmType::prim:
                saveResult("Prim", verticesConf, "matrix");
                break;

            case AlgorithmType::kruskal:
                saveResult("Kruskal", verticesConf, "matrix");
                break;

            case AlgorithmType::dijkstra:
                saveResult("Dijkstra", verticesConf, "matrix");
                break;

            case AlgorithmType::bf:
                saveResult("Bellman-Ford", verticesConf, "matrix");
                break;
        }

        std::cout << "Done vertices config -  " << verticesConf << "\n\n";
        results.clear();
    }

}

void Testing::calculateAlgorithmList(AlgorithmType algorithm)
{
    std::list <double> intervals;
    size_t start;
    size_t finish;

    for(int verticesConf = 30; verticesConf <= 270; verticesConf += 60) {
        for (int density = 25; density <= 100; density += 25)
        {
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


                if (algorithm == AlgorithmType::prim) {
                    watch.startCounting();

                    auto result = Algorithms::primMST(lGraph);

                    intervals.push_back(watch.getTime());

                    delete result;
                }

                if (algorithm == AlgorithmType::kruskal) {
                    watch.startCounting();

                    auto result = Algorithms::kruskalMST(lGraph);

                    intervals.push_back(watch.getTime());

                    delete result;
                }

                if (algorithm == AlgorithmType::dijkstra) {
                    watch.startCounting();


                    auto result = Algorithms::dijkstraPath(lGraph, start, finish);

                    intervals.push_back(watch.getTime());

                    delete result;
                }

                if (algorithm == AlgorithmType::bf) {
                    watch.startCounting();

                    auto result = Algorithms::bfPath(lGraph, start, finish);

                    intervals.push_back(watch.getTime());

                    delete result;
                }

            }
            std::cout << "Done density -  " << density << "\n";
            addSeriesAvg(calcAvg(intervals), density);
            intervals.clear();
        }

        switch (algorithm) {
            case AlgorithmType::prim:
                saveResult("Prim", verticesConf, "list");
                break;

            case AlgorithmType::kruskal:
                saveResult("Kruskal", verticesConf, "list");
                break;

            case AlgorithmType::dijkstra:
                saveResult("Dijkstra", verticesConf, "list");
                break;

            case AlgorithmType::bf:
                saveResult("Bellman-Ford", verticesConf, "list");
                break;
        }

        std::cout << "Done vertices config -  " << verticesConf << "\n\n";
        results.clear();
    }

}

void Testing::saveResult(const std::string &algorithm, size_t verticesNum, const std::string& representation) {
    //Creating write file
    std::ofstream saveFile(algorithm + "//" + representation + "//test - " + std::to_string(verticesNum) + ".txt");

    //Printing opResult objects for each tested operation to the file
    for (const OpResult &result: results) {
        saveFile << result.density << ";" << result.time << "\n";
    }

    saveFile.close();
}