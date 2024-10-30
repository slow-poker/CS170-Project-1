#include "tree.h"
using namespace std;

Tree::Tree(Puzzle startPuzzle) {
    startState = new Node{startPuzzle};
    currState = startState;
}

Tree::~Tree() {

}

void Tree::addChild(Puzzle nodePuzzle) {
   
}

void Tree::removeChild() {

}