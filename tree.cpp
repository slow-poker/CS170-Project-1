#include "tree.h"
using namespace std;

Tree::Tree(Puzzle *startPuzzle) {
    startState = new Node{startPuzzle};
    currState = startState;
}

Tree::~Tree() {

}



void Tree::expandNode() {
    

    //find where 0 is
    unsigned zeroCol, zeroRow = 0;
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
    //check if up is a possible move
    if(operatorCheck(1, )) {

    }
    //check if down is a possible move
    //check if left is a possible move
    //check if right is a possible move

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



