#ifndef __PRIORITYQUEUE__
#define __PRIORITYQUEUE__
#include "node.h"

class PriorityQueue{
    friend class Tree;
    private:
        Node* head;
        PriorityQueue();
        ~PriorityQueue();
        void push(); //push nodes to the queue in order of least to greatest score
        void pop(); //pop

};

#endif


//delete later 