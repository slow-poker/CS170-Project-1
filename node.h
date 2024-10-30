#ifndef __NODE__
#define __NODE__
#include "puzzle.h"

class Node{
    friend class Tree;
    private:
        int priority;
        int depth;
        Puzzle* nodePuzzle;
        Node* parent;
        Node* child1;
        Node* child2;
        Node* child3;
        Node* child4;

    public:
        Node(Puzzle* inputPuzzle) {nodePuzzle = inputPuzzle;} //calculate priority upon creation 
        int getArrayLength(); //returns side length of puzzle square
};

#endif