#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL    0
#endif

#include "Manager.h"
#include "TreeNode.h"

// This queue is Refernce code (Do Not Use directly)


class Queue
{
public:
    int head;
    int tail;
    int size; //Free to define (recommand 100 or 200)
    TreeNode* dat[500];

    Queue(){
        head = 0;
        tail = 0;
        //TreeNode treenode[500];
        /*for (int i = 0; i < 500; i++) {
            ImageNode* n = new ImageNode();
            dat[i] = new TreeNode(n, NULL, NULL);
        }*/
    }
    ~Queue()
    {
        delete[] dat;
    }
    
    void push(TreeNode* tmp) {
        dat[tail++] = tmp;
    }

    void pop() {
        head++;
    }

    TreeNode* top() {
        return dat[head];
    }

    bool empty() {
        return tail == head;
    }

    bool isFull() {
        //Check queue is full or not
    }
};


#endif
