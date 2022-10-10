#ifndef STACK_H
#define STACK_H

#include "TreeNode.h"
#include "Manager.h"

#define IMG_SIZE 512

class TREE_STACK
{
public:
    int idx;
    TreeNode *tree_element;

    TREE_STACK()
    {
        idx = 0;
        tree_element = new TreeNode[IMG_SIZE];
    };

    ~TREE_STACK()
    {
        delete[] tree_element;
    };

    void push(TreeNode tmp)
    {
        tree_element[idx++] = tmp;
    }

    void pop(void)
    {
        if (idx > 0)
            idx--;
    }

    TreeNode top()
    {
        return (tree_element[idx - 1]);
    }

    int empty(void)
    {
        return (idx == 0);
    }
};

class INT_STACK
{
public:
    int idx;
    int *int_element;

    INT_STACK()
    {
        idx = 0;
        int_element = new int[IMG_SIZE * IMG_SIZE];
    };

    ~INT_STACK() {
        delete[] int_element;
    };

    void push(int tmp)
    {
        int_element[idx++] = tmp;
    }

    void pop(void)
    {
        idx--;
    }

    int top()
    {
        return (int_element[idx - 1]);
    }

    bool empty(void)
    {
        return (idx == 0);
    }
};

#endif