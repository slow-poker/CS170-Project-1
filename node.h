#ifndef __NODE__
#define __NODE__
#include "puzzle.h"

class Node{
    private:
        int priority;
        Node* parent = nullptr;
        Node* child1 = nullptr;
        Node* child2 = nullptr;
        Node* child3 = nullptr;
        Node* child4 = nullptr;
    public:
        Node(Puzzle nodePuzzle);
        

};

#endif