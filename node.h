#ifndef __NODE__
#define __NODE__
#include "puzzle.h"

class Node{
    friend class Tree;
    private:
        int priority;
        int depth;
        Node* parent;
        Node* child1; //up
        Node* child2; //down
        Node* child3; //left
        Node* child4; //right

    public:
        Puzzle* nodePuzzle;
        Node(int depth, Puzzle* nodePuzzle, Node* parent); //calculate priority upon creation 
        int getArrayLength(); //returns side length of puzzle square
        
};

#endif