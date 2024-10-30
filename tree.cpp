#include "tree.h"
using namespace std;

Tree::Tree(Puzzle *startPuzzle) {
    startState = new Node{startPuzzle};
    currState = startState;
    nodeQueue.push(startState);
}

Tree::~Tree() {
    //delete tree nodes
    //set pointers to null?
}



void Tree::expandNode() {

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

    //find next states using the 4 operators: up, down, left, right
    Node* puzzleChild = nullptr;
    if(operatorCheck(1 ,zeroRow, zeroCol)) {//check if up is a possible move
        puzzleChild = new Node{currState->depth++, currState->nodePuzzle, currState};                   //duplicate current state
        currState->child1 = puzzleChild;                                                                //setup tree
        puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow-1][zeroCol]);             //perform operation for new puzzle child
        puzzleChild->priority = (puzzleChild->nodePuzzle->misplacedTiles() ) + (puzzleChild->depth);    //set puzzle priority for queue f(n) = h(n) + g(n)
        nodeQueue.push(*puzzleChild);
    }
    if(operatorCheck(2 ,zeroRow, zeroCol)) {//check if down is a possible move
        
    }
    if(operatorCheck(3 ,zeroRow, zeroCol)) {//check if left is a possible move
        
    }
    if(operatorCheck(4 ,zeroRow, zeroCol)) {//check if right is a possible move
        
    }
    puzzleChild = nullptr;
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