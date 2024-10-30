#include "node.h"

Node::Node(Puzzle* inputPuzzle) { //calculate priority and use setter in tree
    priority = -1;
    depth = -1;
    nodePuzzle = inputPuzzle;
    parent = nullptr;
    child1 = nullptr;
    child2 = nullptr;
    child3 = nullptr;
    child4 = nullptr;
} 

int Node::getArrayLength() { sizeof(nodePuzzle->puzzle) / sizeof(nodePuzzle->puzzle[0][0]); }