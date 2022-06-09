#include "Testing.h"
#include "../GraphGenerator/GraphGenerator.h"

MatrixGraph *Testing::mGraph = nullptr;
ListGraph *Testing::lGraph = nullptr;

//Function that calculates average time for provided list with intervals
double Testing::calcAvg(const std::list<double> &dataStr) {
    double avg = 0;

    //Calculating average from provided vector's elements
    for (double result: dataStr) {
        avg += result;
    }
    avg /= double(dataStr.size());

    return avg;
}

//Function that creates single series result and adds it to adequate list
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


//Functions that tests all algorithms for matrix representation
void Testing::calculateAlgorithmsMatrix() {

    //Creating operational variables
    std::list<double> pIntervals;
    std::list<double> kIntervals;
    std::list<double> dIntervals;
    std::list<double> bIntervals;
    size_t start;
    size_t finish;

    //Testing for 5 different vertices numbers
    for (int verticesConf = 30; verticesConf <= 270; verticesConf += 60)
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
                GraphGenerator::generate(density, verticesConf, this->maxElement);
                mGraph = new MatrixGraph(GraphGenerator::edges, verticesConf, GraphGenerator::data);

                //Drawing a pair of vertices for SP algorithms
                while (true) {
                    start = rand() % verticesConf;
                    finish = rand() % verticesConf;

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

                auto result2 = Algorithms::dijkstraPath(mGraph, start, finish);
                dIntervals.push_back(watch.getTime());
                delete result2;


                //Measuring bellman-ford algorithm
                watch.startCounting();


                result2 = Algorithms::bfPath(mGraph, start, finish);
                bIntervals.push_back(watch.getTime());
                delete result2;
            }
            std::cout << "Done density -  " << density << "\n";

            //Creating series results for current density
            addSeriesAvg(calcAvg(pIntervals), density, AlgorithmType::prim);
            addSeriesAvg(calcAvg(kIntervals), density, AlgorithmType::kruskal);
            addSeriesAvg(calcAvg(dIntervals), density, AlgorithmType::dijkstra);
            addSeriesAvg(calcAvg(bIntervals), density, AlgorithmType::bf);

            //Clearing intervals for next density
            pIntervals.clear();
            kIntervals.clear();
            dIntervals.clear();
            bIntervals.clear();
        }

        //Saving results of all algorithms for current vertices number
        saveResult("Prim", verticesConf, "matrix", AlgorithmType::prim);
        saveResult("Kruskal", verticesConf, "matrix", AlgorithmType::kruskal);
        saveResult("Dijkstra", verticesConf, "matrix", AlgorithmType::dijkstra);
        saveResult("Bellman-Ford", verticesConf, "matrix", AlgorithmType::bf);

        std::cout << "Done vertices config -  " << verticesConf << "\n\n";

        //Clearing results for next vertices number
        primResults.clear();
        kruskalResults.clear();
        dijResults.clear();
        bfResults.clear();
    }

}

//Functions that tests all algorithms for list representation
void Testing::calculateAlgorithmsList() {
    //Creating operational variables
    std::list<double> pIntervals;
    std::list<double> kIntervals;
    std::list<double> dIntervals;
    std::list<double> bIntervals;
    size_t start;
    size_t finish;

    //Testing for 5 different vertices numbers
    for (int verticesConf = 30; verticesConf <= 270; verticesConf += 60)
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
                GraphGenerator::generate(density, verticesConf, this->maxElement);
                lGraph = new ListGraph(GraphGenerator::edges, verticesConf, GraphGenerator::data);

                //Drawing a pair of vertices for SP algorithms
                while (true) {
                    start = rand() % verticesConf;
                    finish = rand() % verticesConf;

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

                auto result2 = Algorithms::dijkstraPath(lGraph, start, finish);
                dIntervals.push_back(watch.getTime());
                delete result2;


                //Measuring bellman-ford algorithm
                watch.startCounting();


                result2 = Algorithms::bfPath(lGraph, start, finish);
                bIntervals.push_back(watch.getTime());
                delete result2;
            }
            std::cout << "Done density -  " << density << "\n";

            //Creating series results for current density
            addSeriesAvg(calcAvg(pIntervals), density, AlgorithmType::prim);
            addSeriesAvg(calcAvg(kIntervals), density, AlgorithmType::kruskal);
            addSeriesAvg(calcAvg(dIntervals), density, AlgorithmType::dijkstra);
            addSeriesAvg(calcAvg(bIntervals), density, AlgorithmType::bf);

            //Clearing intervals for next density
            pIntervals.clear();
            kIntervals.clear();
            dIntervals.clear();
            bIntervals.clear();
        }

        //Saving results of all algorithms for current vertices number
        saveResult("Prim", verticesConf, "matrix", AlgorithmType::prim);
        saveResult("Kruskal", verticesConf, "matrix", AlgorithmType::kruskal);
        saveResult("Dijkstra", verticesConf, "matrix", AlgorithmType::dijkstra);
        saveResult("Bellman-Ford", verticesConf, "matrix", AlgorithmType::bf);

        std::cout << "Done vertices config -  " << verticesConf << "\n\n";

        //Clearing results for next vertices number
        primResults.clear();
        kruskalResults.clear();
        dijResults.clear();
        bfResults.clear();
    }
}

//Functions that saves measurements for a single algorithm to .txt file
void Testing::saveResult(const std::string &algorithm, size_t verticesNum, const std::string &representation, AlgorithmType alg) {
    //Creating write file
    std::ofstream saveFile(algorithm + "//" + representation + "//test - " + std::to_string(verticesNum) + ".txt");

    //Choosing right list with results
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