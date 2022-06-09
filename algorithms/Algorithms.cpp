#include "Algorithms.h"
#include "../containers/EdgeHeap/MyHeap.h"

//for matrix implementation
MatrixMSTResult *Algorithms::primMST(MatrixGraph *graph) {
    //preparing variables
    size_t totalCost = 0;
    size_t nodes = graph->getNodesNumber();
    size_t edges = graph->getEdgesNumber();
    MatrixElement **matrix = graph->getMatrix();

    size_t buffSize = (nodes - 1) * 3;
    auto *resultBuff = new size_t[buffSize];
    size_t buffIndex = 0;

    auto *edgeHeap = new MyHeap();

    auto visitedNodes = new int[nodes];
    for (size_t i = 0; i < nodes; i++) {
        visitedNodes[i] = 0;
    }

    //Creating macro for adding node edges heap
    auto addNodeEdges = [&](size_t nodeIndex) {
        for (size_t i = 0; i < edges; i++) {
            if (matrix[nodeIndex][i].type == CellType::empty) {
                continue;
            }

            for (size_t j = 0; j < nodes; j++) {
                if (matrix[j][i].type == CellType::empty) {
                    continue;
                }

                if (visitedNodes[j] != 0) {
                    continue;
                }

                if (matrix[nodeIndex][i].type == CellType::origin) {
                    auto edge = new Edge(nodeIndex, j, matrix[j][i].weight);
                    edgeHeap->add(*edge);
                    break;
                } else {
                    auto edge = new Edge(j, nodeIndex, matrix[j][i].weight);
                    edgeHeap->add(*edge);
                    break;
                }
            }
        }
    };

    size_t currNodeIndex = 0;
    visitedNodes[currNodeIndex] = 1;
    addNodeEdges(currNodeIndex);

    //Creating MST with adequate edges (to non-visited nodes)
    for (size_t i = 0; i < edges; i++) {
        Edge currEdge = edgeHeap->extractRoot();

        if (visitedNodes[currEdge.destination] != 0 && visitedNodes[currEdge.origin] != 0) {
            continue;
        }

        if (visitedNodes[currEdge.destination] == 0) {
            currNodeIndex = currEdge.destination;
        } else {
            currNodeIndex = currEdge.origin;
        }

        resultBuff[3 * buffIndex] = currEdge.origin;
        resultBuff[3 * buffIndex + 1] = currEdge.destination;
        resultBuff[3 * buffIndex + 2] = currEdge.weight;
        totalCost += currEdge.weight;


        visitedNodes[currNodeIndex] = 1;
        addNodeEdges(currNodeIndex);
        buffIndex++;

        if (buffIndex == nodes - 1) {
            break;
        }
    }

    //Creating output matrix and cleaning allocated variables
    auto oMatrix = new MatrixGraph(nodes - 1, nodes, resultBuff);

    delete[] resultBuff;
    delete[] visitedNodes;
    delete edgeHeap;


    return new MatrixMSTResult(oMatrix, totalCost);
}

//for list implementation
ListMSTResult *Algorithms::primMST(ListGraph *graph) {
    //preparing variables
    size_t totalCost = 0;
    size_t nodes = graph->getNodesNumber();
    size_t edges = graph->getEdgesNumber();
    ListGraphElement **lists = graph->getList();

    size_t buffSize = edges * 3;
    auto *resultBuff = new size_t[buffSize];
    size_t buffIndex = 0;

    auto edgeHeap = new MyHeap();

    int *visitedNodes = new int[nodes];
    for (size_t i = 0; i < nodes; i++) {
        visitedNodes[i] = 0;
    }

    //Creating macro for adding nodes edge to heap
    auto addNodeEdges = [&](size_t nodesIndex) {
        for (size_t i = 0; i < nodes; i++) {
            ListGraphElement *list = lists[i];

            if (list == nullptr) {
                continue;
            }

            if (i == nodesIndex) {
                while (list != nullptr) {
                    if (visitedNodes[list->node] == 0) {
                        auto currEdge = new Edge(nodesIndex, list->node, list->weight);
                        edgeHeap->add(*currEdge);
                    }

                    list = list->nextElement;
                }
            }


            while (list != nullptr) {
                if (list->node == nodesIndex && visitedNodes[i] == 0) {
                    auto currEdge = new Edge(i, list->node, list->weight);
                    edgeHeap->add(*currEdge);
                }

                list = list->nextElement;
            }
        }
    };

    size_t currNodeIndex = 0;
    visitedNodes[currNodeIndex] = 1;
    addNodeEdges(currNodeIndex);

    //MST Prim algorithm
    for (size_t i = 0; i < nodes - 1;) {
        Edge currEdge = edgeHeap->extractRoot();

        if (visitedNodes[currEdge.destination] == 0) {
            currNodeIndex = currEdge.destination;

            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;

            totalCost += currEdge.weight;
            visitedNodes[currNodeIndex] = 1;

            addNodeEdges(currNodeIndex);

            buffIndex++;
            i++;
        } else if (visitedNodes[currEdge.origin] == 0) {
            currNodeIndex = currEdge.origin;

            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;

            totalCost += currEdge.weight;
            visitedNodes[currNodeIndex] = 1;

            addNodeEdges(currNodeIndex);

            buffIndex++;
            i++;
        }
    }

    //Creating output list and cleaning up
    auto oList = new ListGraph(nodes - 1, nodes, resultBuff);
    delete[] resultBuff;
    delete edgeHeap;

    return new ListMSTResult(oList, totalCost);
}

//for matrix implementation
MatrixMSTResult *Algorithms::kruskalMST(MatrixGraph *graph) {
    //preparing variables
    size_t totalCost = 0;
    size_t nodes = graph->getNodesNumber();
    size_t edges = graph->getEdgesNumber();
    MatrixElement **matrix = graph->getMatrix();

    size_t buffSize = edges * 3;
    auto *resultBuff = new size_t[buffSize];
    size_t buffIndex = 0;

    auto *edgeHeap = new MyHeap();

    //Creating heap with edges
    for (size_t column = 0; column < edges; column++) {
        int originNode = -1;
        int destNode = -1;
        int edgeWeight = -1;

        for (size_t row = 0; row < nodes; row++) {
            if (matrix[row][column].type == CellType::empty) {
                continue;
            }

            if (matrix[row][column].type == CellType::origin) {
                originNode = row;
                edgeWeight = matrix[row][column].weight;
                continue;
            }

            if (matrix[row][column].type == CellType::destination) {
                destNode = row;
                continue;
            }
        }

        if (destNode > -1 && originNode > -1 && edgeWeight > -1) {
            auto edge = new Edge(originNode, destNode, edgeWeight);
            edgeHeap->add(*edge);
        }
    }

    //Creating variables for determining whether adding edge creates cycle
    size_t node_id[nodes];

    for (size_t i = 0; i < nodes; i++) {
        node_id[i] = i;
    }

    //Searching for proper edges
    for (size_t j = 0; j < edges; j++) {
        auto currEdge = edgeHeap->extractRoot();

        if (node_id[currEdge.origin] != node_id[currEdge.destination]) {
            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;
            totalCost += currEdge.weight;

            int checkId = node_id[currEdge.destination];
            int newId = node_id[currEdge.origin];

            for (size_t i = 0; i < nodes; i++) {
                if (node_id[i] == checkId) {
                    node_id[i] = newId;
                }
            }

            buffIndex++;

            if (buffIndex == nodes - 1) {
                break;
            }
        }
    }

    //Creating output matrix and cleaning up
    auto oMatrix = new MatrixGraph(nodes - 1, nodes, resultBuff);
    delete[] resultBuff;
    delete edgeHeap;

    return new MatrixMSTResult(oMatrix, totalCost);
}

//for list implementation
ListMSTResult *Algorithms::kruskalMST(ListGraph *graph) {
    //preparing variables
    size_t totalCost = 0;
    size_t nodes = graph->getNodesNumber();
    size_t edges = graph->getEdgesNumber();
    ListGraphElement **lists = graph->getList();

    size_t buffSize = edges * 3;
    auto *resultBuff = new size_t[buffSize];
    size_t buffIndex = 0;

    auto edgeHeap = new MyHeap();

    //Creating heap with all edges
    for (size_t i = 0; i < nodes; i++) {
        ListGraphElement *list = lists[i];

        while (list != nullptr) {
            auto currEdge = new Edge(i, list->node, list->weight);
            edgeHeap->add(*currEdge);

            list = list->nextElement;
        }
    }


    //Creating variables for determining whether adding edge creates cycle
    size_t node_id[nodes];

    for (size_t i = 0; i < nodes; i++) {
        node_id[i] = i;
    }

    //Searching for proper edges
    for (size_t j = 0; j < edges; j++) {
        auto currEdge = edgeHeap->extractRoot();

        if (node_id[currEdge.origin] != node_id[currEdge.destination]) {
            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;
            totalCost += currEdge.weight;

            int checkId = node_id[currEdge.destination];
            int newId = node_id[currEdge.origin];

            for (size_t i = 0; i < nodes; i++) {
                if (node_id[i] == checkId) {
                    node_id[i] = newId;
                }
            }

            buffIndex++;

            if (buffIndex == nodes - 1) {
                break;
            }
        }
    }

    //Creating output list and cleaning up
    auto oList = new ListGraph(nodes - 1, nodes, resultBuff);
    delete[] resultBuff;
    delete edgeHeap;

    return new ListMSTResult(oList, totalCost);
}

//for matrix implementation
SPResult *Algorithms::dijkstraPath(MatrixGraph *graph, const size_t &start, const size_t &finish) {

    size_t nodes = graph->getNodesNumber();
    size_t edges = graph->getEdgesNumber();
    MatrixElement **matrix = graph->getMatrix();

    //preparing variables
    MyArray<size_t> edgesCosts;
    MyArray<int> visitedNodes;
    MyArray<int> previousNodes;
    MyArray<int> reachingCosts;
    MyArray<int> cost;
    MyArray<PElement> pathArray;
    size_t totalCost = 0;

    //Filing array of edges costs
    for (size_t column = 0; column < edges; column++) {
        for (size_t row = 0; row < nodes; row++) {
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
    for (int i = 0; i < nodes; i++) {
        visitedNodes.addBack(-1);
        previousNodes.addBack(-1);
        cost.addBack(-1);
        reachingCosts.addBack(INT_MAX);
    }

    reachingCosts[start] = 0;
    size_t currentNode = start;
    size_t nodesToCheck = nodes;

    //Creating macro which marks visited node in table and chooses next node
    auto moveToNextNode = [&]() {
        visitedNodes[currentNode] = 0;
        nodesToCheck--;
        size_t shortestPath = INT_MAX;
        for (size_t i = 0; i < nodes; i++) {
            if (visitedNodes[i] == -1 && reachingCosts[i] < shortestPath) {
                shortestPath = reachingCosts[i];
                currentNode = i;
            }
        }
    };

    //Checking all nodes
    while (nodesToCheck > 0) {
        //Checking whether any edge comes from current node
        for (size_t edge = 0; edge < edges; edge++) {
            if (matrix[currentNode][edge].type != CellType::origin) {
                continue;
            }

            for (size_t node = 0; node < nodes; node++) {
                if (matrix[node][edge].type != CellType::destination) {
                    continue;
                }

                //After founding edge checking whether it is optimal at the moment
                if (reachingCosts[currentNode] + edgesCosts[edge] < reachingCosts[node]) {
                    //Updating minimal reach cost to destination node
                    reachingCosts[node] = reachingCosts[currentNode] + edgesCosts[edge];
                    previousNodes[node] = currentNode;
                    cost[node] = edgesCosts[edge];
                }

                break;
            }
        }

        moveToNextNode();
    }

    currentNode = finish;

    //Creating result path from by jumping end node to start one with minimal reach costs
    while (currentNode != start) {
        totalCost += cost[currentNode];
        pathArray.addFront(PElement(cost[currentNode], previousNodes[currentNode], currentNode));
        currentNode = previousNodes[currentNode];

        if (currentNode == -1) {
            return new SPResult("", totalCost);
        }
    }

    std::string path;
    for (int i = 0; i < pathArray.getSize(); i++) {
        path.append(pathArray[i].toString());
    }

    return new SPResult(path, totalCost);
}

//for list implementation
SPResult *Algorithms::dijkstraPath(ListGraph *graph, const size_t &start, const size_t &finish) {
    size_t nodes = graph->getNodesNumber();
    ListGraphElement **list = graph->getList();

    //Creating operational variables
    MyArray<int> visitedNodes;
    MyArray<int> previousNodes;
    MyArray<int> reachingCosts;
    MyArray<int> cost;
    MyArray<PElement> pathArray;
    size_t totalCost = 0;

    //Filling other tmp arrays
    for (int i = 0; i < nodes; i++) {
        visitedNodes.addBack(-1);
        previousNodes.addBack(-1);
        cost.addBack(-1);
        reachingCosts.addBack(INT_MAX);
    }

    reachingCosts[start] = 0;
    size_t currentNode = start;
    size_t nodesToCheck = nodes;

    //Creating macro which marks visited node in table and chooses next node
    auto moveToNextNode = [&]() {
        visitedNodes[currentNode] = 0;
        nodesToCheck--;
        size_t shortestPath = INT_MAX;
        for (size_t i = 0; i < nodes; i++) {
            if (visitedNodes[i] == -1 && reachingCosts[i] < shortestPath) {
                shortestPath = reachingCosts[i];
                currentNode = i;
            }
        }
    };

    //Checking all nodes
    while (nodesToCheck > 0) {
        //Checking whether any edge comes from current node
        ListGraphElement *currElement = list[currentNode];
        while (currElement != nullptr) {

            //After founding edge checking whether it is optimal at the moment
            if (reachingCosts[currentNode] + currElement->weight < reachingCosts[currElement->node]) {

                //Updating minimal reach cost to destination node
                reachingCosts[currElement->node] = reachingCosts[currentNode] + currElement->weight;
                previousNodes[currElement->node] = currentNode;
                cost[currElement->node] = currElement->weight;
            }

            currElement = currElement->nextElement;
        }

        moveToNextNode();
    }

    currentNode = finish;

    //Creating result path from by jumping end node to start one with minimal reach costs
    while (currentNode != start) {
        totalCost += cost[currentNode];
        pathArray.addFront(PElement(cost[currentNode], previousNodes[currentNode], currentNode));
        currentNode = previousNodes[currentNode];

        if (currentNode == -1) {
            return new SPResult("", totalCost);
        }
    }

    std::string path;
    for (int i = 0; i < pathArray.getSize(); i++) {
        path.append(pathArray[i].toString());
    }
    return new SPResult(path, totalCost);

}


//for matrix implementation
SPResult *Algorithms::bfPath(MatrixGraph *graph, const size_t &start, const size_t &finish) {
    size_t nodes = graph->getNodesNumber();
    size_t edges = graph->getEdgesNumber();
    MatrixElement **matrix = graph->getMatrix();

    //Creating operational variables
    MyArray<size_t> edgesCosts;
    MyArray<int> previousNode;
    MyArray<int> reachCosts;
    MyArray<int> cost;
    MyArray<PElement> pathArray;
    size_t totalCost = 0;

    //Filing array of edges costs
    for (size_t column = 0; column < edges; column++) {
        for (size_t row = 0; row < nodes; row++) {
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
    for (int i = 0; i < nodes; i++) {
        previousNode.addBack(-1);
        cost.addBack(-1);
        reachCosts.addBack(INT_MAX);
    }

    reachCosts[start] = 0;
    bool costChange;


    //Checking all nodes
    for (int i = 0; i < nodes - 1; i++) {
        costChange = false;

        for (int currentNode = 0; currentNode < nodes; currentNode++) {
            //Checking whether any edge comes from current node
            for (size_t edge = 0; edge < edges; edge++) {
                if (matrix[currentNode][edge].type != CellType::origin) {
                    continue;
                }

                for (size_t node = 0; node < nodes; node++) {
                    if (matrix[node][edge].type != CellType::destination) {
                        continue;
                    }

                    //After founding edge checking whether it is optimal at the moment
                    if (reachCosts[currentNode] + edgesCosts[edge] < reachCosts[node]) {
                        //Updating minimal reach cost to destination node
                        reachCosts[node] = reachCosts[currentNode] + edgesCosts[edge];
                        previousNode[node] = currentNode;
                        cost[node] = edgesCosts[edge];
                        costChange = true;
                    }

                    break;
                }
            }
        }

        if (!costChange) {
            break;
        }
    }

    size_t currNode = finish;

    //Creating result path from by jumping end node to start one with minimal reach costs
    while (currNode != start) {
        totalCost += cost[currNode];
        pathArray.addFront(PElement(cost[currNode], previousNode[currNode], currNode));
        currNode = previousNode[currNode];

        if (currNode == -1) {
            return new SPResult("", totalCost);
        }
    }

    std::string path;
    for (int i = 0; i < pathArray.getSize(); i++) {
        path.append(pathArray[i].toString());
    }
    return new SPResult(path, totalCost);
}

//for list implementation
SPResult *Algorithms::bfPath(ListGraph *graph, const size_t &start, const size_t &finish) {
    size_t nodes = graph->getNodesNumber();
    ListGraphElement **list = graph->getList();

    //Creating operational variables
    MyArray<int> previousNode;
    MyArray<int> reachCosts;
    MyArray<int> cost;
    MyArray<PElement> pathArray;
    size_t totalCost = 0;

    //Filling other tmp arrays
    for (int i = 0; i < nodes; i++) {
        previousNode.addBack(-1);
        cost.addBack(-1);
        reachCosts.addBack(INT_MAX);
    }

    reachCosts[start] = 0;
    bool costChange;

    //Checking all nodes
    for (int i = 0; i < nodes - 1; i++) {
        costChange = false;

        for (int currentNode = 0; currentNode < nodes; currentNode++) {
            //Checking whether any edge comes from current node
            ListGraphElement *currElement = list[currentNode];

            while (currElement != nullptr) {

                //After founding edge checking whether it is optimal at the moment
                if (reachCosts[currentNode] + currElement->weight < reachCosts[currElement->node]) {

                    //Updating minimal reach cost to destination node
                    reachCosts[currElement->node] = reachCosts[currentNode] + currElement->weight;
                    previousNode[currElement->node] = currentNode;
                    cost[currElement->node] = currElement->weight;
                    costChange = true;
                }

                currElement = currElement->nextElement;
            }
        }

        if (!costChange) {
            break;
        }

    }

    size_t currentNode = finish;

    //Creating result path from by jumping end node to start one with minimal reach costs
    while (currentNode != start) {
        totalCost += cost[currentNode];
        pathArray.addFront(PElement(cost[currentNode], previousNode[currentNode], currentNode));
        currentNode = previousNode[currentNode];

        if (currentNode == -1) {
            return new SPResult("", totalCost);
        }
    }

    std::string path;
    for (int i = 0; i < pathArray.getSize(); i++) {
        path.append(pathArray[i].toString());
    }
    return new SPResult(path, totalCost);

}