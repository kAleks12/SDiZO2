#include "Simulation.h"
#include "../GraphGenerator/GraphGenerator.h"

MatrixGraph *Simulation::mGraph = nullptr;
ListGraph *Simulation::lGraph = nullptr;

//Function that calculates average time for provided list with intervals
double Simulation::calcAvg(const std::list<double> &dataStr) {
    double avg = 0;

    //Calculating average from provided vector's elements
    for (double result: dataStr) {
        avg += result;
    }
    avg /= double(dataStr.size());

    return avg;
}

//Function that creates single series result and adds it to adequate list
void Simulation::addSeriesAvg(double avg, size_t density, AlgorithmName alg) {
    OperationResultData result;

    //Creating result object for specific structure and operation
    result.time = avg;
    result.density = density;

    //Adding created object to vector with all operations' results
    switch (alg) {
        case AlgorithmName::prim:
            primResults.push_back(result);
            break;

        case AlgorithmName::kruskal:
            kruskalResults.push_back(result);
            break;

        case AlgorithmName::dijkstra:
            dijResults.push_back(result);
            break;

        case AlgorithmName::bf:
            bfResults.push_back(result);
            break;
    }
}


//Functions that tests all algorithms for matrix representation
void Simulation::calculateAlgorithmsMatrix() {

    //Creating operational variables
    std::list<double> pIntervals;
    std::list<double> kIntervals;
    std::list<double> dIntervals;
    std::list<double> bIntervals;
    size_t start;
    size_t finish;

    //Simulation for 5 different vertices numbers
    for (int nodesCount = 10; nodesCount <= 210; nodesCount += 50)
    {
        //...and 4 densities
        for (int density = 25; density <= 100; density += 25)
        {
            //...and 20 different graphs
            for (int i = 0; i < sampleSize; ++i)
            {
                //Deleting old graph
                delete mGraph;

                if (density == 100) {
                    density--;
                }

                //Generating new graph represented by matrix
                GraphGenerator::generate(density, nodesCount, this->maxElementValue);
                mGraph = new MatrixGraph(GraphGenerator::edges, nodesCount, GraphGenerator::data);

                //Drawing a pair of vertices for SP algorithms
                while (true) {
                    start = rand() % nodesCount;
                    finish = rand() % nodesCount;

                    if (start != finish) {
                        break;
                    }
                }

                //Measuring prim algorithm
                watch.startCounting();

                auto result = Algorithms::primMST(mGraph);
                pIntervals.push_back(watch.getTime());
                delete result;


                //Measuring kruskal algorithm
                watch.startCounting();

                result = Algorithms::kruskalMST(mGraph);
                kIntervals.push_back(watch.getTime());
                delete result;


                //Measuring dijkstra algorithm
                watch.startCounting();

                auto result2 = Algorithms::dijkstra(mGraph, start, finish);
                dIntervals.push_back(watch.getTime());
                delete result2;


                //Measuring bellman-ford algorithm
                watch.startCounting();


                result2 = Algorithms::bellmanFord(mGraph, start, finish);
                bIntervals.push_back(watch.getTime());
                delete result2;
            }
            std::cout << "for -  " << density << "\n";

            //Creating series results for current density
            addSeriesAvg(calcAvg(pIntervals), density, AlgorithmName::prim);
            addSeriesAvg(calcAvg(kIntervals), density, AlgorithmName::kruskal);
            addSeriesAvg(calcAvg(dIntervals), density, AlgorithmName::dijkstra);
            addSeriesAvg(calcAvg(bIntervals), density, AlgorithmName::bf);

            //Clearing intervals for next density
            pIntervals.clear();
            kIntervals.clear();
            dIntervals.clear();
            bIntervals.clear();
        }

        //Saving results of all algorithms for current nodes number
        saveResult("Prim", nodesCount, "matrix", AlgorithmName::prim);
        saveResult("Kruskal", nodesCount, "matrix", AlgorithmName::kruskal);
        saveResult("Dijkstra", nodesCount, "matrix", AlgorithmName::dijkstra);
        saveResult("Bellman-Ford", nodesCount, "matrix", AlgorithmName::bf);

        std::cout << "Done vertices config -  " << nodesCount << "\n\n";

        //Clearing results for next vertices number
        primResults.clear();
        kruskalResults.clear();
        dijResults.clear();
        bfResults.clear();
    }
}

//Functions that tests all algorithms for list representation
void Simulation::calculateAlgorithmsList() {
    //Creating operational variables
    std::list<double> pIntervals;
    std::list<double> kIntervals;
    std::list<double> dIntervals;
    std::list<double> bIntervals;
    size_t start;
    size_t finish;

    //Simulation for 5 different vertices numbers
    for (int nodesCount = 10; nodesCount <= 210; nodesCount += 50)
    {
        //...and 4 densities
        for (int density = 25; density <= 100; density += 25)
        {
            //...and 20 different graphs
            for (int i = 0; i < sampleSize; ++i)
            {
                //Deleting old graph
                delete lGraph;

                if (density == 100) {
                    density--;
                }

                //Generating new graph represented by list
                GraphGenerator::generate(density, nodesCount, this->maxElementValue);
                lGraph = new ListGraph(GraphGenerator::edges, nodesCount, GraphGenerator::data);

                //Drawing a pair of vertices for SP algorithms
                while (true) {
                    start = rand() % nodesCount;
                    finish = rand() % nodesCount;

                    if (start != finish) {
                        break;
                    }
                }

                //Measuring prim algorithm
                watch.startCounting();

                auto result = Algorithms::primMST(lGraph);
                pIntervals.push_back(watch.getTime());
                delete result;


                //Measuring kruskal algorithm
                watch.startCounting();

                result = Algorithms::kruskalMST(lGraph);
                kIntervals.push_back(watch.getTime());
                delete result;


                //Measuring dijkstra algorithm
                watch.startCounting();

                auto result2 = Algorithms::dijkstra(lGraph, start, finish);
                dIntervals.push_back(watch.getTime());
                delete result2;


                //Measuring bellman-ford algorithm
                watch.startCounting();


                result2 = Algorithms::bellmanFord(lGraph, start, finish);
                bIntervals.push_back(watch.getTime());
                delete result2;
            }
            std::cout << "Done density -  " << density << "\n";

            //Creating series results for current density
            addSeriesAvg(calcAvg(pIntervals), density, AlgorithmName::prim);
            addSeriesAvg(calcAvg(kIntervals), density, AlgorithmName::kruskal);
            addSeriesAvg(calcAvg(dIntervals), density, AlgorithmName::dijkstra);
            addSeriesAvg(calcAvg(bIntervals), density, AlgorithmName::bf);

            //Clearing intervals for next density
            pIntervals.clear();
            kIntervals.clear();
            dIntervals.clear();
            bIntervals.clear();
        }

        //Saving results of all algorithms for current vertices number
        saveResult("Prim", nodesCount, "list", AlgorithmName::prim);
        saveResult("Kruskal", nodesCount, "list", AlgorithmName::kruskal);
        saveResult("Dijkstra", nodesCount, "list", AlgorithmName::dijkstra);
        saveResult("Bellman-Ford", nodesCount, "list", AlgorithmName::bf);

        std::cout << "Done vertices config -  " << nodesCount << "\n\n";

        //Clearing results for next vertices number
        primResults.clear();
        kruskalResults.clear();
        dijResults.clear();
        bfResults.clear();
    }
}

//Functions that saves measurements for a single algorithm to .txt file
void Simulation::saveResult(const std::string &algorithm, size_t verticesNum, const std::string &representation, AlgorithmName alg) {
    //Creating write file
    std::ofstream saveFile(algorithm + "//" + representation + "//test - " + std::to_string(verticesNum) + ".txt");

    //Choosing right list with results
    auto results = primResults;

    switch (alg) {
        case AlgorithmName::prim:
            results = primResults;
            break;

        case AlgorithmName::kruskal:
            results = kruskalResults;
            break;

        case AlgorithmName::dijkstra:
            results = dijResults;
            break;

        case AlgorithmName::bf:
            results = bfResults;
            break;
    }

    //Printing operation result data objects for each tested operation to the file
    for (const OperationResultData &result: results) {
        saveFile << result.density << ";" << result.time << "\n";
    }

    saveFile.close();
}