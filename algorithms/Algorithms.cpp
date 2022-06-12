//
// Created by kacper on 19.05.2022.
//

#include "Algorithms.hpp"
#include "../containers/EdgeHeap/EdgeHeap.hpp"

///////////////////////////////
//    PRIM IMPLEMENTATIONS   //
///////////////////////////////
//MATRIX
MatrixMSTResult* Algorithms::primMST(IncidencyMatrix *graph) {
    //Setting up operational variables
    size_t totalCost = 0;
    size_t vertices = graph->getVerticesNumber();
    size_t edges = graph->getEdgesNumber();
    MatrixCell **matrix = graph->getMatrix();

    size_t buffSize = (vertices - 1) * 3;
    auto *resultBuff = new size_t[buffSize];
    size_t buffIndex = 0;

    auto *eHeap = new EdgeHeap();

    auto visitedVertices = new int[vertices];
    for (size_t i = 0; i < vertices; i++) {
        visitedVertices[i] = 0;
    }

    //Creating 'macro' for adding specific vertex's edges to queue heap
    auto addVertexEdges = [&](size_t vertexIndex) {
        for (size_t i = 0; i < edges; i++) {
            if (matrix[vertexIndex][i].type == CellType::empty) {
                continue;
            }

            for (size_t j = 0; j < vertices; j++) {
                if (matrix[j][i].type == CellType::empty) {
                    continue;
                }

                if (visitedVertices[j] != 0) {
                    continue;
                }


                if (matrix[vertexIndex][i].type == CellType::origin) {
                    auto edge = new Edge(vertexIndex, j, matrix[j][i].weight);
                    eHeap->add(*edge);
                    break;
                } else {
                    auto edge = new Edge(j, vertexIndex, matrix[j][i].weight);
                    eHeap->add(*edge);
                    break;
                }
            }
        }
    };

    size_t currVertexIndex = 0;
    visitedVertices[currVertexIndex] = 1;
    addVertexEdges(currVertexIndex);

    //Creating mst with right edges (to vertices that have not been visited yet)
    for (size_t i = 0; i < edges; i++) {
        Edge currEdge = eHeap->extractRoot();


        if (visitedVertices[currEdge.destination] != 0 && visitedVertices[currEdge.origin] != 0) {
            continue;
        }

        if (visitedVertices[currEdge.destination] == 0) {
            currVertexIndex = currEdge.destination;
        } else {
            currVertexIndex = currEdge.origin;
        }

        resultBuff[3 * buffIndex] = currEdge.origin;
        resultBuff[3 * buffIndex + 1] = currEdge.destination;
        resultBuff[3 * buffIndex + 2] = currEdge.weight;
        totalCost += currEdge.weight;


        visitedVertices[currVertexIndex] = 1;
        addVertexEdges(currVertexIndex);
        buffIndex++;

        if (buffIndex == vertices - 1) {
            break;
        }

    }

    //Creating output matrix and cleaning allocated variables
    auto oMatrix = new IncidencyMatrix(vertices - 1, vertices, resultBuff);

    delete[] resultBuff;
    delete[] visitedVertices;
    delete eHeap;


    return new MatrixMSTResult(oMatrix, totalCost);
}

//LIST
ListMSTResult* Algorithms::primMST(AdjacencyList *graph) {
    //Setting up operational variables
    size_t totalCost = 0;
    size_t vertices = graph->getVerticesNumber();
    size_t edges = graph->getEdgesNumber();
    ALElement **lists = graph->getList();

    size_t buffSize = edges * 3;
    auto *resultBuff = new size_t[buffSize];
    size_t buffIndex = 0;

    auto eHeap = new EdgeHeap();

    int *visitedVertices = new int[vertices];
    for (size_t i = 0; i < vertices; i++) {
        visitedVertices[i] = 0;
    }

    //Creating 'macro' for adding certain vertex's edges to queue heap
    auto addVertexEdges = [&](size_t vertexIndex) {
        ALElement *list = lists[vertexIndex];

        if (list == nullptr) {
            return;
        }

        while (list != nullptr) {
            if (visitedVertices[list->vertex] == 0) {
                auto currEdge = new Edge(vertexIndex, list->vertex, list->weight);
                eHeap->add(*currEdge);
            }

            list = list->nextElement;
        }
    };

    size_t currVertexIndex = 0;
    visitedVertices[currVertexIndex] = 1;
    addVertexEdges(currVertexIndex);

    //Creating mst with prim algorithm
    for (size_t i = 0; i < vertices - 1;) {
        Edge currEdge = eHeap->extractRoot();

        if (visitedVertices[currEdge.destination] == 0) {
            currVertexIndex = currEdge.destination;

            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;

            totalCost += currEdge.weight;
            visitedVertices[currVertexIndex] = 1;

            addVertexEdges(currVertexIndex);

            buffIndex++;
            i++;
        } else if (visitedVertices[currEdge.origin] == 0) {
            currVertexIndex = currEdge.origin;

            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;

            totalCost += currEdge.weight;
            visitedVertices[currVertexIndex] = 1;

            addVertexEdges(currVertexIndex);

            buffIndex++;
            i++;
        }
    }

    //Creating output list and cleaning allocated variables
    auto oList = new AdjacencyList(vertices - 1, vertices, resultBuff);
    delete[] resultBuff;
    delete eHeap;

    return new ListMSTResult(oList, totalCost);
}


///////////////////////////////
//  KRUSKAL IMPLEMENTATIONS  //
///////////////////////////////
//MATRIX
MatrixMSTResult* Algorithms::kruskalMST(IncidencyMatrix *graph) {
    //Setting operational variables
    size_t totalCost = 0;
    size_t vertices = graph->getVerticesNumber();
    size_t edges = graph->getEdgesNumber();
    MatrixCell **matrix = graph->getMatrix();

    size_t buffSize = edges * 3;
    auto *resultBuff = new size_t[buffSize];
    size_t buffIndex = 0;

    auto *eHeap = new EdgeHeap();

    //Creating queue heap with all edges
    for (size_t column = 0; column < edges; column++) {
        int originV = -1;
        int destV = -1;
        int edgeWeight = -1;

        for (size_t row = 0; row < vertices; row++) {
            if (matrix[row][column].type == CellType::empty) {
                continue;
            }

            if (matrix[row][column].type == CellType::origin) {
                originV = row;
                edgeWeight = matrix[row][column].weight;
                continue;
            }

            if (matrix[row][column].type == CellType::destination) {
                destV = row;
                continue;
            }
        }

        if (destV > -1 && originV > -1 && edgeWeight > -1) {
            auto edge = new Edge(originV, destV, edgeWeight);
            eHeap->add(*edge);
        }
    }

    //Creating variables for determining if adding edge creates cycle
    size_t vertex_id[vertices];

    for (size_t i = 0; i < vertices; i++) {
        vertex_id[i] = i;
    }

    //Searching for right edges
    for (size_t j = 0; j < edges; j++) {
        auto currEdge = eHeap->extractRoot();

        if (vertex_id[currEdge.origin] != vertex_id[currEdge.destination]) {
            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;
            totalCost += currEdge.weight;

            int checkId = vertex_id[currEdge.destination];
            int newId = vertex_id[currEdge.origin];

            for (size_t i = 0; i < vertices; i++) {
                if (vertex_id[i] == checkId) {
                    vertex_id[i] = newId;
                }
            }

            buffIndex++;

            if (buffIndex == vertices - 1) {
                break;
            }
        }
    }

    //Creating output matrix and deleting allocated variables
    auto oMatrix = new IncidencyMatrix(vertices - 1, vertices, resultBuff);
    delete[] resultBuff;
    delete eHeap;


    return new MatrixMSTResult(oMatrix, totalCost);
}

//LIST
ListMSTResult* Algorithms::kruskalMST(AdjacencyList *graph) {
    //Setting up operational variables
    size_t totalCost = 0;
    size_t vertices = graph->getVerticesNumber();
    size_t edges = graph->getEdgesNumber();
    ALElement **lists = graph->getList();

    size_t buffSize = edges * 3;
    auto *resultBuff = new size_t[buffSize];
    size_t buffIndex = 0;

    auto eHeap = new EdgeHeap();

    //Creating queue heap with all edges
    for (size_t i = 0; i < vertices; i++) {
        ALElement *list = lists[i];

        while (list != nullptr) {
            auto currEdge = new Edge(i, list->vertex, list->weight);
            eHeap->add(*currEdge);

            list = list->nextElement;
        }
    }


    //Creating variables for determining if adding edge creates cycle
    size_t vertex_id[vertices];

    for (size_t i = 0; i < vertices; i++) {
        vertex_id[i] = i;
    }

    //Searching for right edges
    for (size_t j = 0; j < edges; j++) {
        auto currEdge = eHeap->extractRoot();

        if (vertex_id[currEdge.origin] != vertex_id[currEdge.destination]) {
            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;
            totalCost += currEdge.weight;

            int checkId = vertex_id[currEdge.destination];
            int newId = vertex_id[currEdge.origin];

            for (size_t i = 0; i < vertices; i++) {
                if (vertex_id[i] == checkId) {
                    vertex_id[i] = newId;
                }
            }

            buffIndex++;

            if (buffIndex == vertices - 1) {
                break;
            }
        }
    }

    //Creating output list and cleaning variables
    auto oList = new AdjacencyList(vertices - 1, vertices, resultBuff);
    delete[] resultBuff;
    delete eHeap;

    return new ListMSTResult(oList, totalCost);

}



/////////////////////////////////
//  DIJSKTRA IMPLEMENTATIONS  //
////////////////////////////////
//MATRIX
SPResult* Algorithms::dijkstraPath(IncidencyMatrix *graph, const size_t &start, const size_t &finish) {
    size_t vertices = graph->getVerticesNumber();
    size_t edges = graph->getEdgesNumber();
    MatrixCell **matrix = graph->getMatrix();

    //Creating operational variables
    DynamicArray<size_t> edgesCosts;
    DynamicArray<int> visitedV;
    DynamicArray<int> previousV;
    DynamicArray<int> reachCosts;
    DynamicArray<int> cost;
    DynamicArray<PElement> pathArray;
    size_t totalCost = 0;

    //Filing array of edges' costs
    for (size_t column = 0; column < edges; column++) {
        for (size_t row = 0; row < vertices; row++) {
            if (matrix[row][column].type == CellType::empty) {
                continue;
            }

            if (matrix[row][column].type == CellType::origin || matrix[row][column].type == CellType::destination) {
                edgesCosts.addBack(matrix[row][column].weight);
                break;
            }
        }
    }

    //Filling other tmp arrays
    for (int i = 0; i < vertices; i++) {
        visitedV.addBack(-1);
        previousV.addBack(-1);
        cost.addBack(-1);
        reachCosts.addBack(INT_MAX);
    }

    reachCosts[start] = 0;
    size_t currentVertex = start;
    size_t verticesToCheck = vertices;

    //Creating macro which marks visited vertex in table and chooses next vertex
    auto moveToNextVertex = [&]() {
        visitedV[currentVertex] = 0;
        verticesToCheck--;
        size_t shortestPath = INT_MAX;
        for (size_t i = 0; i < vertices; i++) {
            if (visitedV[i] == -1 && reachCosts[i] < shortestPath) {
                shortestPath = reachCosts[i];
                currentVertex = i;
            }
        }
    };

    //Checking all vertices
    while (verticesToCheck > 0) {
        //Checking whether any edge comes from current vertex
        for (size_t edge = 0; edge < edges; edge++) {
            if (matrix[currentVertex][edge].type != CellType::origin) {
                continue;
            }

            for (size_t vertex = 0; vertex < vertices; vertex++) {
                if (matrix[vertex][edge].type != CellType::destination) {
                    continue;
                }

                //After founding edge checking whether it is optimal at the moment
                if (reachCosts[currentVertex] + edgesCosts[edge] < reachCosts[vertex]) {
                    //Updating minimal reach cost to destination vertex
                    reachCosts[vertex] = reachCosts[currentVertex] + edgesCosts[edge];
                    previousV[vertex] = currentVertex;
                    cost[vertex] = edgesCosts[edge];
                }

                break;
            }
        }

        moveToNextVertex();
    }

    currentVertex = finish;

    //Creating result path from by jumping end vertex to start one with minimal reach costs
    while (currentVertex != start) {
        totalCost += cost[currentVertex];
        pathArray.addFront(PElement(cost[currentVertex], previousV[currentVertex], currentVertex));
        currentVertex = previousV[currentVertex];

        if (currentVertex == -1) {
            return new SPResult("", totalCost);
        }
    }

    std::string path;
    for (int i = 0; i < pathArray.getSize(); i++) {
        path.append(pathArray[i].toString());
    }

    return new SPResult(path, totalCost);
}

//LIST
SPResult* Algorithms::dijkstraPath(AdjacencyList *graph, const size_t &start, const size_t &finish) {
    size_t vertices = graph->getVerticesNumber();
    ALElement **list = graph->getList();

    //Creating operational variables
    DynamicArray<int> visitedV;
    DynamicArray<int> previousV;
    DynamicArray<int> reachCosts;
    DynamicArray<int> cost;
    DynamicArray<PElement> pathArray;
    size_t totalCost = 0;

    //Filling other tmp arrays
    for (int i = 0; i < vertices; i++) {
        visitedV.addBack(-1);
        previousV.addBack(-1);
        cost.addBack(-1);
        reachCosts.addBack(INT_MAX);
    }

    reachCosts[start] = 0;
    size_t currentVertex = start;
    size_t verticesToCheck = vertices;

    //Creating macro which marks visited vertex in table and chooses next vertex
    auto moveToNextVertex = [&]() {
        visitedV[currentVertex] = 0;
        verticesToCheck--;
        size_t shortestPath = INT_MAX;
        for (size_t i = 0; i < vertices; i++) {
            if (visitedV[i] == -1 && reachCosts[i] < shortestPath) {
                shortestPath = reachCosts[i];
                currentVertex = i;
            }
        }
    };

    //Checking all vertices
    while (verticesToCheck > 0) {
        //Checking whether any edge comes from current vertex
        ALElement *currElement = list[currentVertex];
        while (currElement != nullptr) {

            //After founding edge checking whether it is optimal at the moment
            if (reachCosts[currentVertex] + currElement->weight < reachCosts[currElement->vertex]) {

                //Updating minimal reach cost to destination vertex
                reachCosts[currElement->vertex] = reachCosts[currentVertex] + currElement->weight;
                previousV[currElement->vertex] = currentVertex;
                cost[currElement->vertex] = currElement->weight;
            }

            currElement = currElement->nextElement;
        }

        moveToNextVertex();
    }

    currentVertex = finish;

    //Creating result path from by jumping end vertex to start one with minimal reach costs
    while (currentVertex != start) {
        totalCost += cost[currentVertex];
        pathArray.addFront(PElement(cost[currentVertex], previousV[currentVertex], currentVertex));
        currentVertex = previousV[currentVertex];

        if (currentVertex == -1) {
            return new SPResult("", totalCost);
        }
    }

    std::string path;
    for (int i = 0; i < pathArray.getSize(); i++) {
        path.append(pathArray[i].toString());
    }
    return new SPResult(path, totalCost);

}



/////////////////////////////////////
//  BELLMAN-FORD IMPLEMENTATIONS  //
////////////////////////////////////
//MATRIX
SPResult* Algorithms::bfPath(IncidencyMatrix *graph, const size_t &start, const size_t &finish) {
    size_t vertices = graph->getVerticesNumber();
    size_t edges = graph->getEdgesNumber();
    MatrixCell **matrix = graph->getMatrix();

    //Creating operational variables
    DynamicArray<size_t> edgesCosts;
    DynamicArray<int> previousV;
    DynamicArray<int> reachCosts;
    DynamicArray<int> cost;
    DynamicArray<PElement> pathArray;
    size_t totalCost = 0;

    //Filing array of edges' costs
    for (size_t column = 0; column < edges; column++) {
        for (size_t row = 0; row < vertices; row++) {
            if (matrix[row][column].type == CellType::empty) {
                continue;
            }

            if (matrix[row][column].type == CellType::origin || matrix[row][column].type == CellType::destination) {
                edgesCosts.addBack(matrix[row][column].weight);
                break;
            }
        }
    }

    //Filling other tmp arrays
    for (int i = 0; i < vertices; i++) {
        previousV.addBack(-1);
        cost.addBack(-1);
        reachCosts.addBack(INT_MAX);
    }

    reachCosts[start] = 0;
    bool costChange;


    //Checking all vertices
    for(int i = 0; i < vertices -1; i++){
        costChange = false;

        for(int currentVertex = 0; currentVertex < vertices; currentVertex++) {
            //Checking whether any edge comes from current vertex
            for (size_t edge = 0; edge < edges; edge++) {
                if (matrix[currentVertex][edge].type != CellType::origin) {
                    continue;
                }

                for (size_t vertex = 0; vertex < vertices; vertex++) {
                    if (matrix[vertex][edge].type != CellType::destination) {
                        continue;
                    }

                    //After founding edge checking whether it is optimal at the moment
                    if (reachCosts[currentVertex] + edgesCosts[edge] < reachCosts[vertex]) {
                        //Updating minimal reach cost to destination vertex
                        reachCosts[vertex] = reachCosts[currentVertex] + edgesCosts[edge];
                        previousV[vertex] = currentVertex;
                        cost[vertex] = edgesCosts[edge];
                        costChange = true;
                    }

                    break;
                }
            }
        }

        if(!costChange){
            break;
        }
    }

    size_t currV = finish;

    //Creating result path from by jumping end vertex to start one with minimal reach costs
    while (currV != start) {
        totalCost += cost[currV];
        pathArray.addFront(PElement(cost[currV], previousV[currV], currV));
        currV = previousV[currV];

        if (currV == -1) {
            return new SPResult("", totalCost);
        }
    }

    std::string path;
    for (int i = 0; i < pathArray.getSize(); i++) {
        path.append(pathArray[i].toString());
    }
    return new SPResult(path, totalCost);
}

//LIST
SPResult* Algorithms::bfPath(AdjacencyList *graph, const size_t &start, const size_t &finish) {
    size_t vertices = graph->getVerticesNumber();
    ALElement **list = graph->getList();

    //Creating operational variables
    DynamicArray<int> previousV;
    DynamicArray<int> reachCosts;
    DynamicArray<int> cost;
    DynamicArray<PElement> pathArray;
    size_t totalCost = 0;

    //Filling other tmp arrays
    for (int i = 0; i < vertices; i++) {
        previousV.addBack(-1);
        cost.addBack(-1);
        reachCosts.addBack(INT_MAX);
    }

    reachCosts[start] = 0;
    bool costChange;

    //Checking all vertices
    for(int i = 0; i < vertices -1; i++){
        costChange = false;

        for(int currentVertex = 0; currentVertex < vertices; currentVertex++) {
            //Checking whether any edge comes from current vertex
            ALElement *currElement = list[currentVertex];

            while (currElement != nullptr) {

                //After founding edge checking whether it is optimal at the moment
                if (reachCosts[currentVertex] + currElement->weight < reachCosts[currElement->vertex]) {

                    //Updating minimal reach cost to destination vertex
                    reachCosts[currElement->vertex] = reachCosts[currentVertex] + currElement->weight;
                    previousV[currElement->vertex] = currentVertex;
                    cost[currElement->vertex] = currElement->weight;
                    costChange = true;
                }

                currElement = currElement->nextElement;
            }
        }

        if(!costChange){
            break;
        }

    }

    size_t currentVertex = finish;

    //Creating result path from by jumping end vertex to start one with minimal reach costs
    while (currentVertex != start) {
        totalCost += cost[currentVertex];
        pathArray.addFront(PElement(cost[currentVertex], previousV[currentVertex], currentVertex));
        currentVertex = previousV[currentVertex];

        if (currentVertex == -1) {
            return new SPResult("", totalCost);
        }
    }

    std::string path;
    for (int i = 0; i < pathArray.getSize(); i++) {
        path.append(pathArray[i].toString());
    }
    return new SPResult(path, totalCost);

}