#include "tree.h"
using namespace std;

Tree::Tree(Puzzle *startPuzzle) {
    startState = new Node{0, startPuzzle, nullptr};
    currState = startState;
    nodeQueue.push(*startState);
}

Tree::~Tree() {
    //delete tree nodes
    destroyTree(startState);
    //set pointers to null?
    currState = nullptr;
    startState = nullptr;
    
}

void Tree::destroyTree(Node* nodePtr) { //put root ptr in, recursively deletes all children
    if(nodePtr->child1 != nullptr)
        destroyTree(nodePtr->child1);
    if(nodePtr->child2 != nullptr)
        destroyTree(nodePtr->child2);
    if(nodePtr->child3 != nullptr)
        destroyTree(nodePtr->child3);
    if(nodePtr->child4 != nullptr)
        destroyTree(nodePtr->child4);
    
    //has no children left
    delete nodePtr;
    nodePtr = nullptr;
}



void Tree::expandNode() { //find all possible moves from the currState node, create their puzzleNodes and add them to the priority queue

    //find where 0 is
    unsigned zeroCol = 0, zeroRow = 0;
    bool earlyEnd = false;

    for(zeroRow = 0; zeroRow < 3; ++zeroRow) {
        for(zeroCol = 0; zeroCol < 0; ++zeroCol) {
            if(currState->nodePuzzle->puzzle[zeroRow][zeroCol] == 0) {
                earlyEnd = true;
                break;
            }            
        }
        if(earlyEnd)
        break;
    }

    nodeQueue.pop(); //remove expanded node from queue

    //find next states using the 4 operators: up, down, left, right
    Node* puzzleChild = nullptr;
    if(operatorCheck(1 ,zeroRow, zeroCol)) {//check if up is a possible move
        puzzleChild = new Node{currState->depth++, currState->nodePuzzle, currState};                   //duplicate current state
        currState->child1 = puzzleChild;                                                                //setup tree
        puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow-1][zeroCol]);             //perform operation for new puzzle child
        puzzleChild->priority = (puzzleChild->nodePuzzle->puzzleEucladian() ) + (puzzleChild->depth);   //set puzzle priority for queue with f(n) = h(n) + g(n)
        nodeQueue.push(*puzzleChild);                                                                   //push puzzle to queue
    }                                                                                                   //repeat for other moves 
    if(operatorCheck(2 ,zeroRow, zeroCol)) {//check if down is a possible move
        puzzleChild = new Node{currState->depth++, currState->nodePuzzle, currState};
        currState->child2 = puzzleChild;
        puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow+1][zeroCol]);
        puzzleChild->priority = (puzzleChild->nodePuzzle->puzzleEucladian() ) + ( puzzleChild->depth);
        nodeQueue.push(*puzzleChild);
    }
    if(operatorCheck(3 ,zeroRow, zeroCol)) {//check if left is a possible move
        puzzleChild = new Node{currState->depth++, currState->nodePuzzle, currState};
        currState->child3 = puzzleChild;
        puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow][zeroCol-1]);
        puzzleChild->priority = (puzzleChild->nodePuzzle->puzzleEucladian() ) + ( puzzleChild->depth);
        nodeQueue.push(*puzzleChild);
    }
    if(operatorCheck(4 ,zeroRow, zeroCol)) {//check if right is a possible move
        puzzleChild = new Node{currState->depth++, currState->nodePuzzle, currState};
        currState->child4 = puzzleChild;
        puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow][zeroCol+1]);
        puzzleChild->priority = (puzzleChild->nodePuzzle->puzzleEucladian() ) + ( puzzleChild->depth);
        nodeQueue.push(*puzzleChild);
    }
    puzzleChild = nullptr;

    //queue is setup with children
    //move currstate to top of queue (c++ std priority queue returns const Node so this is done using the tree)

    if(currState == nodeQueue.top().self);
    
}

bool Tree::operatorCheck(int move, int zeroRow, int zeroCol) { // 1=up, 2=down, 3=left, 4=right; checks if the move is a valid state
    unsigned arrMaxIndex = currState->getArrayLength() - 1;
    if(move = 1) { //up
        if(zeroRow <= arrMaxIndex && zeroRow > 0)
        return true;
        else return false;
    }
    if(move = 2) { //down
        if(zeroRow < arrMaxIndex && zeroRow >= 0 )
        return true;
        else return false;
    }    
    if(move = 3) { //left
        if(zeroCol <= arrMaxIndex && zeroCol > 0)
        return true;
        else return false;
    }    
    if(move = 4) { //right
        if(zeroCol < arrMaxIndex && zeroCol >= 0)
        return true;
        else return false;
    }
    return false;    
}