#include "tree.h"
#include <iostream>
#include <memory>
using namespace std;

Tree::Tree(Puzzle *startPuzzle) {
    startState = new Node{1, startPuzzle, nullptr};
    currState = startState;
    nodeQueue.push(*startState);
}

Tree::~Tree() {
    //delete tree nodes
    destroyTree(startState);
    //set pointers to null?
    delete currState;
    delete startState;
    currState = nullptr;
    startState = nullptr;
    longestQueue = 1;
    currentQueue = 1;
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



void Tree::expandNode(int algo) { //find all possible moves from the currState node, create their puzzleNodes and add them to the priority queue

    expanded++;
    currentQueue--;
    //find where 0 is
    unsigned zeroCol = 0, zeroRow = 0;
    bool earlyEnd = false;

    for(zeroRow = 0; zeroRow < 3; ++zeroRow) {  // finds and saves location of 0 in the puzzle
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
   for (int move = 1; move <= 4; ++move) {   //checks if move is valid 
        if (operatorCheck(move, zeroRow, zeroCol)) {
            Node* puzzleChild = new Node{currState->depth + 1, new Puzzle(*currState->nodePuzzle), currState}; //creates child puzzle copy 

            // Handle movement based on the move
            if (move == 1) puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow - 1][zeroCol]); // Up
            else if (move == 2) puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow + 1][zeroCol]); // Down
            else if (move == 3) puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow][zeroCol - 1]); // Left
            else if (move == 4) puzzleChild->nodePuzzle->swap(puzzleChild->nodePuzzle->puzzle[zeroRow][zeroCol + 1]); // Right

            if (checkIfVisited(*puzzleChild->nodePuzzle)) { // deletes the child if it was already seen
                delete puzzleChild;
            } else {
                if (move == 1) currState->child1 = puzzleChild;  // assigns the node as the child of the parent
                else if (move == 2) currState->child2 = puzzleChild;
                else if (move == 3) currState->child3 = puzzleChild;
                else if (move == 4) currState->child4 = puzzleChild;
                currentQueue++;
                if(longestQueue < currentQueue)
                longestQueue = currentQueue;
            }
        }
   }

               Node* arr[] = {currState->child1, currState->child2, currState->child3, currState->child4};  // creates and array of the children and assigns them priority based of the algorithm sleected

        for (int i = 0; i < 4; ++i) {
            Node* child = arr[i];
            if (child != nullptr) {
                // Calculate priority based on algorithm
                if (algo == 1) {
                    child->priority = child->depth;
                } else if (algo == 2) {
                    child->priority = child->nodePuzzle->misplacedTiles() + child->depth;
                } else if (algo == 3) {
                    child->priority = child->nodePuzzle->puzzleEucladian() + child->depth;
                }
                /*cout << "Child priorirty " << child->priority << endl;
                // Print which child is being processed
                
                cout << "Processing child " << (i + 1) << endl; // i + 1 to match child1, child2, etc.
                child->nodePuzzle->printPuzzle();
                */
                nodeQueue.push(*child);   // then we push it to the node quue and push the puzzle to the list of states already seen
                //cout << "pushed";           // we have to push the states after we have calculated their priorirty 
                seen.push_back(*child->nodePuzzle);  


            }
        }

    //queue is setup with children
    //move currstate to top of queue (c++ std priority queue returns const Node so this is done using the tree)
    currState->visited = 0;

    //if(currState == nodeQueue.top().self);   // idk what this line is for which is why I commented it 
    //cout << "raaaaaan";
}

bool Tree::operatorCheck(int move, int zeroRow, int zeroCol) { // 1=up, 2=down, 3=left, 4=right; checks if the move is a valid state
    unsigned arrMaxIndex = currState->getArrayLength() - 1;
    //note: had to change some of this bc it was always returning valid move
    if (move == 1) { // Up
        return zeroRow > 0; // Can move up if not at the top row
    }
    if (move == 2) { // Down
        return zeroRow < 2; // Can move down if not at the bottom row
    }    
    if (move == 3) { // Left
        return zeroCol > 0; // Can move left if not in the first column
    }    
    if (move == 4) { // Right
        return zeroCol < 2; // Can move right if not in the last column
    }
    
    return false;  
}


int Tree::explore(int algo){
    int hn;
    int gn;

    if(algo == 1){  //initial hearistic for starting node 
        hn = 0;
    } else if (algo == 2){
        hn = currState->nodePuzzle->misplacedTiles();
    } else if (algo == 3){
        hn = currState->nodePuzzle->puzzleEucladian();
    }
    currState->priority = hn;

    seen.push_back(*currState->nodePuzzle);
    while(true){
        if (nodeQueue.empty() == true){
            cout << "We cannot find a solution :(" << endl;
            return 0;
        }

        currState = new Node(nodeQueue.top());
        nodeQueue.pop();

        if(currState->nodePuzzle->goalPuzzle() == true){  //chekcs if we are at goal state 
            cout << "congrats we found !" << endl; //finish later
            currState->nodePuzzle->printPuzzle();
            printSolution(currState);

            return currState->depth;
        } else {
            if(currState->parent == nullptr){
                cout << endl << "expanding state: " << endl;
                currState->nodePuzzle->printPuzzle();
                cout << endl;

            } else {
                gn = currState->depth;
                hn = currState->priority - currState->depth;
                cout << "The best way to expand with g(n) = " << gn << " nd h(n) = " << hn << "..." << endl;
                currState->nodePuzzle->printPuzzle();
                cout << "expanding node: "<< endl << endl;
            }
        }

        
        expandNode(algo);  //begin s expanding tree based of algorthm 
        
        //once expand state has run, it wil push the calid children to the nmodeQueue and this loop will repeat itself unitl the 
        // goal is met or the nodeQueue becomes empty 
                    
       }
}

bool Tree::checkIfVisited(Puzzle currPuzzle) {  //checks if this was a previously visited state 
    for ( Puzzle state : seen) {
        bool match = true; // Assume it matches initially
        for (int i = 0; i < 3; ++i) { // Assuming a 3x3 puzzle
            for (int j = 0; j < 3; ++j) {
                if (currPuzzle.puzzle[i][j] != state.puzzle[i][j]) {
                    match = false; // Found a mismatch
                    break; // No need to check further in this state
                }
            }
            if (!match) break; // Exit outer loop if already found a mismatch
        }
        if (match) {
            //cout << "State seen before" << endl;
            return true; // Found a match
        }
    }
    //cout << "State not seen before" << endl;
    return false; // No matches found
}

int Tree::expandedNodes(){
    return expanded;
}

int Tree::longest(){
    return longestQueue;
}

void Tree::printSolution(Node* state){
    Node* currPuzzle = state;
    vector<Node*> path;

    while (currPuzzle != nullptr) {
        path.push_back(currPuzzle);
        currPuzzle = currPuzzle->parent;
    }

    cout << endl << "Here is the solution: " << endl << endl;

    // Print the solution path in the correct order (start to goal)
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        (*it)->nodePuzzle->printPuzzle();
        if (it + 1 != path.rend()) { // Check if more nodes remain
            cout << "expand to... " << endl << endl;
        }
    }
}
