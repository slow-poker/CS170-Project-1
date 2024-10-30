#include "node.h"

Node::Node(int depth, Puzzle* nodePuzzle, Node* parent) { //calculate priority and use setter in tree
    priority = -1;
    this->depth = depth;
    this->nodePuzzle = nodePuzzle;
    this->parent = parent;
    child1 = nullptr;
    child2 = nullptr;
    child3 = nullptr;
    child4 = nullptr;
} 

int Node::getArrayLength() { sizeof(nodePuzzle->puzzle) / sizeof(nodePuzzle->puzzle[0][0]); }