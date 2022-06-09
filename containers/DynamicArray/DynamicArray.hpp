//
// Created by kacperA on 14.03.2022.
//

#pragma once

#include <iostream>
#include <list>
#include <vector>

template<typename T>
class DynamicArray {
    //Class variables
    T *head = nullptr;
    size_t size = 0;

public:
    //Class methods
    DynamicArray(); //Constructor
    ~DynamicArray(); //Destructor

    T &operator[](const size_t &index); //Overload of [] operator

    void addBack(const T &val); //Add val at the end of the table
    void addFront(const T &val); //Add val at the beginning of the table
    void removeBack(); //Remove element from the end of the table
    void removeFront(); //Remove element from the front of the table

    //Return curr size of the table
    int getSize(){
        return  this->size;
    }
};

#include "DynamicArray.tpp"