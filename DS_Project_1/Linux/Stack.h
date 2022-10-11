#ifndef STACK_H
#define STACK_H

#include "TreeNode.h"
#include "Manager.h"

#define IMG_SIZE 512

template <class T>
class STACK
{
public:
    int idx;
    T *tree_element;

    STACK()
    {
        idx = 0;
        tree_element = new T[IMG_SIZE * IMG_SIZE];
    };

    ~STACK()
    {
        delete[] tree_element;
    };

    void push(T tmp)
    {
        tree_element[idx++] = tmp;
    }

    void pop(void)
    {
        if (idx > 0)
            idx--;
    }

    T top(void)
    {
        return (tree_element[idx - 1]);
    }

    bool empty(void)
    {
        return (idx == 0);
    }
};

#endif