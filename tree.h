#ifndef __TREE_H__
#define __TREE_H__
#include "node.h"
#include "priorityQueue.h"



class Tree{
    private:
        Node* startState;
        Node* currState;
        PriorityQueue* Queue;
        void addChild(Puzzle nodePuzzle); //adds a child to the currState from queue
        void removeChild(); //removes a child from the currState
    public:
        Tree(Puzzle startPuzzle);
        ~Tree();
        void expand(); //expands node 
};



#endif