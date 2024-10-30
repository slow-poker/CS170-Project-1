#ifndef __TREE_H__
#define __TREE_H__
#include "node.h"
#include <vector>
#include <queue>
using namespace std;



class Tree{
    private:
        Node* startState;
        Node* currState;
        priority_queue <Node, vector<int>, lessThanByPriority> gq; 
        bool operatorCheck(int move, int zeroRow, int zeroCol);
        

        // void addChild(Puzzle nodePuzzle); //adds a child to the currState from queue
        // void removeChild(); //removes a child from the currState
    public:
        Tree(Puzzle *startPuzzle);
        ~Tree();
        void expandNode(); //adds 4 children to priority queue
};




#endif