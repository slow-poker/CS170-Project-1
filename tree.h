#ifndef __TREE_H__
#define __TREE_H__
#include "node.h"
#include <queue>
using namespace std;

class Tree{
    private:
        Node* startState;
        Node* currState;
        bool operatorCheck(int move, int zeroRow, int zeroCol);
        void Tree::destroyTree(Node* nodePtr); //helper for tree destructor
    public:
        Tree(Puzzle *startPuzzle);
        ~Tree();
        void expandNode(); //adds all possible puzzle children to priority queue, removes currState from queue, currState points to node at the top of queue
        struct lessThanByPriority { //used for tree priority queue
            bool operator()(Node const & lhs, Node const & rhs) {return lhs.priority < rhs.priority;}
        };
        priority_queue<Node, vector<Node>, lessThanByPriority> nodeQueue; 
};

#endif