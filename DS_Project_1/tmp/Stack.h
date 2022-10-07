#ifndef STACK_H
#define STACK_H

#include "Manager.h"
#include "TreeNode.h"

#define IMG_SIZE 512

class TREE_STACK
{
public:
    int pos;
    TreeNode *dat[1000];

    TREE_STACK()
    {
        pos = 0;
    };

    ~TREE_STACK();

    void push(TreeNode *tmp)
    {
        dat[pos++] = tmp;
    }

    void pop(void)
    {
        if (pos > 0)
            pos--;
    }

    TreeNode *top()
    {
        return (dat[pos - 1]);
    }

    int empty(void)
    {
        return (pos == 0);
    }
};

class INT_STACK
{
public:
    int pos;
    int data[IMG_SIZE * IMG_SIZE + 1];

    INT_STACK()
    {
        pos = 0;
    };

    ~INT_STACK();

    void push(int tmp)
    {
        data[pos++] = tmp;
    }

    void pop(void)
    {
        if (pos > 0)
            pos--;
    }

    int top()
    {
        return (data[pos - 1]);
    }

    int empty(void)
    {
        return (pos == 0);
    }
};

#endif