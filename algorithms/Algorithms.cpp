//
// Created by kacpe on 19.05.2022.
//

#include "Algorithms.h"
#include "../containers/EdgeHeap/EdgeHeap.hpp"

IncidencyMatrix *Algorithms::primMST(IncidencyMatrix *graph) {
    size_t vertices = graph->getVerticesNumber();
    size_t edges = graph->getEdgesNumber();
    MatrixCell** matrix = graph->getMatrix();

    size_t buffSize = edges*3;
    auto * resultBuff = new size_t[buffSize];
    size_t buffIndex = 0;

    auto* eHeap = new EdgeHeap();

    int* visitedVertices = new int[vertices];
    for(size_t i = 0; i < vertices; i++){
        visitedVertices[i] = 0;
    }

    auto addVertexEdges = [&](size_t vertexIndex)
    {
        for (size_t i = 0; i < edges; i++)
        {
            if (matrix[vertexIndex][i].type == CellType::empty)
            {
                continue;
            }

            for (size_t j = 0; j < vertices; j++)
            {
                if (matrix[j][i].type == CellType::empty || j == vertexIndex)
                {
                    continue;
                }

                if (visitedVertices[j] != 0)
                {
                    continue;
                }
                auto edge = new Edge(vertexIndex, j, matrix[j][i].weight);
                eHeap->add(*edge);
            }
        }
    };

    size_t currVertexIndex = 0;
    visitedVertices[currVertexIndex] = 1;
    addVertexEdges(currVertexIndex);

    for(size_t i= 0; i < vertices - 1; ){
        Edge currEdge = eHeap->extractRoot();

        if(visitedVertices[currEdge.destination] == 0 ){
            currVertexIndex = currEdge.destination;
            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;

            visitedVertices[currVertexIndex] = 1;
            addVertexEdges(currVertexIndex);
            buffIndex++;
            i++;
        }
    }

    auto aMatrix = new IncidencyMatrix(vertices - 1, vertices, resultBuff);
    delete [] resultBuff;
    delete eHeap;

    return aMatrix;
}

AdjacencyList *Algorithms::primMST(AdjacencyList *graph) {
    size_t vertices = graph->getVerticesNumber();
    size_t edges = graph->getEdgesNumber();
    ALElement** lists = graph->getList();

    size_t buffSize = edges*3;
    auto * resultBuff = new size_t [buffSize];
    size_t buffIndex = 0;

    auto eHeap = new EdgeHeap();

    int* visitedVertices = new int[vertices];
    for(size_t i = 0; i < vertices; i++){
        visitedVertices[i] = 0;
    }

    auto addVertexEdges = [&](size_t vertexIndex)
    {
        for (size_t i = 0; i < vertices; i++){
            ALElement* list = lists[i];

            if (list == nullptr)
            {
                continue;
            }

            if(i == vertexIndex){
                while (list != nullptr)
                {
                    if (visitedVertices[list->vertex] == 0)
                    {
                        auto currEdge = new Edge(vertexIndex, list->vertex, list->weight);
                        eHeap->add(*currEdge);
                    }

                    list = list->nextElement;
                }
            }


            while (list != nullptr)
            {
                if (list->vertex == vertexIndex && visitedVertices[i] == 0)
                {
                    auto currEdge = new Edge(i, list->vertex, list->weight);
                    eHeap->add(*currEdge);
                }

                list = list->nextElement;
            }
        }
    };

    size_t currVertexIndex = 0;
    visitedVertices[currVertexIndex] = 1;
    addVertexEdges(currVertexIndex);
    eHeap->print();

    for(size_t i= 0; i < vertices - 1; ){
        Edge currEdge = eHeap->extractRoot();

        if (visitedVertices[currEdge.destination] == 0)
        {
            currVertexIndex = currEdge.destination;
            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;
            visitedVertices[currVertexIndex] = 1;
            addVertexEdges(currVertexIndex);

            buffIndex++;
            i++;
        }
        else if(visitedVertices[currEdge.origin] == 0)
        {
            currVertexIndex = currEdge.origin;
            resultBuff[3 * buffIndex] = currEdge.origin;
            resultBuff[3 * buffIndex + 1] = currEdge.destination;
            resultBuff[3 * buffIndex + 2] = currEdge.weight;
            visitedVertices[currVertexIndex] = 1;
            addVertexEdges(currVertexIndex);

            buffIndex++;
            i++;
        }
    }

    auto nList = new AdjacencyList(vertices - 1, vertices, resultBuff);
    delete [] resultBuff;
    delete eHeap;

    return nList;
}
