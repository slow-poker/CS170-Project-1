#include "tree.h"
#include <iostream>
#include <memory>
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
        for(zeroCol = 0; zeroCol < 3; ++zeroCol) {
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
        puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow-1][zeroCol]);             //perform operation for new puzzle child
        
        if(checkIfVisited(*puzzleChild->nodePuzzle)){
            delete puzzleChild;
        } else {
            currState->child1 = puzzleChild;                                                                //setup tree
            nodeQueue.push(*puzzleChild); 
        }                                                                  //push puzzle to queue
    }                                                                                                   //repeat for other moves 
    if(operatorCheck(2 ,zeroRow, zeroCol)) {//check if down is a possible move
        puzzleChild = new Node{currState->depth++, currState->nodePuzzle, currState};
        puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow+1][zeroCol]);
        if(checkIfVisited(*puzzleChild->nodePuzzle)){
            delete puzzleChild;
        } else {
            currState->child2 = puzzleChild;                                                                //setup tree
            nodeQueue.push(*puzzleChild); 
        }   
    }
    if(operatorCheck(3 ,zeroRow, zeroCol)) {//check if left is a possible move
        puzzleChild = new Node{currState->depth++, currState->nodePuzzle, currState};
        puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow][zeroCol-1]);
        if(checkIfVisited(*puzzleChild->nodePuzzle)){
            delete puzzleChild;
        } else {
            currState->child3 = puzzleChild;                                                                //setup tree
            nodeQueue.push(*puzzleChild); 
        }   
    }
    if(operatorCheck(4 ,zeroRow, zeroCol)) {//check if right is a possible move
        puzzleChild = new Node{currState->depth++, currState->nodePuzzle, currState};
        puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow][zeroCol+1]);
        if(checkIfVisited(*puzzleChild->nodePuzzle)){
            delete puzzleChild;
        } else {
            currState->child4 = puzzleChild;                                                                //setup tree
            nodeQueue.push(*puzzleChild); 
        }   
    }
    puzzleChild = nullptr;

    //queue is setup with children
    //move currstate to top of queue (c++ std priority queue returns const Node so this is done using the tree)
    currState->visited = 0;

    if(currState == nodeQueue.top().self);
    cout << "raaaaaan";
}

bool Tree::operatorCheck(int move, int zeroRow, int zeroCol) { // 1=up, 2=down, 3=left, 4=right; checks if the move is a valid state
    unsigned arrMaxIndex = currState->getArrayLength() - 1;
    if(move == 1) { //up
        if(zeroRow <= arrMaxIndex && zeroRow > 0)
        return true;
        else return false;
    }
    if(move == 2) { //down
        if(zeroRow < arrMaxIndex && zeroRow >= 0 )
        return true;
        else return false;
    }    
    if(move == 3) { //left
        if(zeroCol <= arrMaxIndex && zeroCol > 0)
        return true;
        else return false;
    }    
    if(move == 4) { //right
        if(zeroCol < arrMaxIndex && zeroCol >= 0)
        return true;
        else return false;
    }
    return false;    
}


int Tree::explore(int algo){

    int hn;
    int gn;

    if(algo == 1){
        hn = 0;
    } else if (algo == 2){
        hn = currState->nodePuzzle->misplacedTiles();
    } else if (algo == 3){
        hn = currState->nodePuzzle->puzzleEucladian();
    }
    cout << "ran";
    currState->priority = hn;

    seen.push_back(*currState->nodePuzzle);

    while(true){
        if (nodeQueue.empty() == true){
            cout << "We cannot find a solution :(" << endl;
            return 0;
        }
 


       if(currState->nodePuzzle->goalPuzzle() == true){
        cout << "congrats we found !" << endl; //finish later
        return 1;
       } else {
        cout << "expanding";
       }

       //currState = &nodeQueue.top();
       shared_ptr<Node> currState = make_shared<Node>(nodeQueue.top());

       nodeQueue.pop();
        
        expandNode();
        
               return 0;
           

       
        



       Node* arr[] = {currState->child1, currState->child2, currState->child3, currState->child4};


       for(Node* child : arr){
            if(child != nullptr){
                if(algo ==1 ){
                    child->priority = child->depth;
                } else if(algo == 2){
                    child->priority = child->nodePuzzle->misplacedTiles() + child->depth;
                } else if(algo == 3){
                    child->priority = child->nodePuzzle->puzzleEucladian() + child->depth;
                }
            }
            nodeQueue.push(*child);
            seen.push_back(*child->nodePuzzle);

                    
       }

       
       
    }

    //contemplating






    return 3;
}

bool Tree::checkIfVisited(Puzzle currPuzzle){
    for(Puzzle states : seen){
            if (currPuzzle.puzzle == states.puzzle){
                return true;
            }
    }
    return false; 
}

