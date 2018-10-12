// Author: Devin Piner
// Filename: Node.h
// Description: Interface of the Node class
// Last Updated: February 20, 2017

#ifndef HW5_NODE_H
#define HW5_NODE_H

#include "PCB.h"

struct Node {
    PCB data;
    Node* next = nullptr;
};

#endif //HW5_NODE_H
