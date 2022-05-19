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

void EdgeHeap::print() {
    //Checking whether heap's body is empty
    if (this->size == 0) {
        std::cout << "Heap is empty\n\n";
        return;
    }
    std::cout << "Contents of heap:\n\n";

    // Calculating heap depth
    size_t depth = getDepth();
    getDepth();

    // Calculating maximum number of elements
    size_t maxSize = pow(2, depth);

    //Setting operational variables
    bool end = false;
    size_t first = 0;
    size_t last = 1;

    size_t space = maxSize;

    while (!end) {
        // Printing spaces before each tree level
        std::cout << std::string(space / 2 * 3, ' ');

        // Printing nodes on current heap level
        for (size_t i = first; i < last; i++) {
            if (i >= this->size) {
                end = true;
                break;
            }

            // Checking if table on current index is not empty
            std::cout << body[i].weight << std::string(space * 3, ' ');

        }

        std::cout << "\n";

        // Changing indexes or last and first node on each tree level
        first = last;
        last = 2 * last + 1;

        // Changing size of space between nodes
        space = space / 2;
    }
    std::cout << "\nSize of heap: " << this->size;
    std::cout << "\n\n";

}

int EdgeHeap::getDepth() {
    //Creating operational variables
    size_t last = 1;
    size_t level = 0;

    //Calculating number of heap's levels
    while (last <= size) {
        level++;
        last = 2 * last + 1;
    }
    return level;
}