#ifndef __NODE__
#define __NODE__
#include "puzzle.h"

class Node{
    friend class Tree;
    friend class lessThanByPriority;
    private:
        int priority;
        Puzzle* nodePuzzle;
        Node* parent = nullptr;
        Node* child1 = nullptr;
        Node* child2 = nullptr;
        Node* child3 = nullptr;
        Node* child4 = nullptr;
        int getArrayLength() { sizeof(nodePuzzle->puzzle) / sizeof(nodePuzzle->puzzle[0][0]);
}

    public:
        Node(){priority = 0; nodePuzzle = nullptr;}
        Node(Puzzle* inputPuzzle) {nodePuzzle = inputPuzzle;} //calculate priority upon creation 
        
};

struct lessThanByPriority { //used for tree priority queue
    bool operator()(Node const & p1, Node const & p2) {return p1.priority < p2.priority;}
};

#endif