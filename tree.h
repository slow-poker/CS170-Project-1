#ifndef __TREE_H__
#define __TREE_H__
#include <vector>
#include <queue>
#include <memory>
#include "node.h"
#include "puzzle.h"



class Tree{
    private:
        int expanded;
        int longestQueue;
        Node* startState;
        Node* currState;
        bool operatorCheck(int move, int zeroRow, int zeroCol);
        void destroyTree(Node* nodePtr); //helper for tree destructor
        std::vector<Puzzle> seen;


    public:
        Tree(Puzzle *startPuzzle);
        ~Tree();
        void expandNode(int ); //adds all possible puzzle children to priority queue, removes currState from queue, currState points to node at the top of queue
        struct lessThanByPriority { //used for tree priority queue
            bool operator()(Node const & lhs, Node const & rhs) {return lhs.priority > rhs.priority;}
        };
        std::priority_queue<Node, std::vector<Node>, lessThanByPriority> nodeQueue; 
        int explore(int);
        bool checkIfVisited(Puzzle currPuzzle);
        int expandedNodes();
        int longest();

};

#endif