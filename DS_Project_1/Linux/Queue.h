#ifndef QUEUE_H
#define QUEUE_H

#include "Manager.h"
#include "TreeNode.h"

class MINI_QUEUE
{
public:
    int head;
    int tail;
    int size;

    TreeNode *dat[100];

    MINI_QUEUE()
    {
        head = 0;
        tail = 0;
    };

    ~MINI_QUEUE();

    void push(TreeNode *tmp)
    {
        dat[tail++] = tmp;
    }

    void pop()
    {
        head++;
    }

    TreeNode *top()
    {
        return (dat[head]);
    }

    bool empty()
    {
        return (tail == head);
    }

    bool isFull()
    {
        return (tail == 1001);
    }
};

#endif
