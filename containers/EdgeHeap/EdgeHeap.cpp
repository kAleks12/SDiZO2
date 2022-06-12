//
// Created by kacper on 18.03.2022.
//


#include <fstream>
#include "EdgeHeap.hpp"

Edge EdgeHeap::extractRoot() {
    //Inserting root to variable
    Edge root = body[0];

    //Checking whether heap has only one element
    if (size == 1) {
        //Removing root from the heap's body
        body.removeFront();
        this->size--;
        return root;
    }

    //Swapping first and last elements in heap's body and removing root
    body[0] = body[size - 1];
    size--;
    body.removeBack();

    //Restoring heap
    minHeapify(0);

    return root;
}

void EdgeHeap::add(const Edge &val) {
    //Inserting new val at last index of the body
    size++;
    body.addBack(val);
    size_t index = size - 1;


    //Restoring min heap

    while (index != 0 && body[getParent(index)] > body[index]) {
        Edge tmp = body[getParent(index)];
        body[getParent(index)] = body[index];
        body[index] = tmp;
        index = getParent(index);
    }
}

void EdgeHeap::minHeapify(int index) {
    //Creating operational variables
    size_t leftSon = getLeft(index);
    size_t rightSon = getRight(index);
    size_t smallest = index;

    //Checking whether left son is within body bounds and whether its value is
    // smaller than the original elements' one
    if (leftSon < size && body[leftSon] < body[smallest]) {
        smallest = leftSon;
    }

    //Checking whether right son is within body bounds and whether its value is
    // smaller than smallest' one
    if (rightSon < size && body[rightSon] < body[smallest]) {
        smallest = rightSon;
    }

    //Checking whether the index with the smallest value is not the original one
    //and swapping values from the smallest index and original one
    if (smallest != index) {
        Edge tmp = body[smallest];
        body[smallest] = body[index];
        body[index] = tmp;

        //Checking rest of the indexes down the heap's body
        minHeapify(smallest);
    }
}