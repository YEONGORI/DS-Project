#ifndef QUEUE_H
#define QUEUE_H

#include "Manager.h"
#include "TreeNode.h"


class TREE_QUEUE
{
public:
    int head;
    int tail;
    int size;

    TreeNode *dat[1000];

    TREE_QUEUE()
    {
        head = 0;
        tail = 0;
    };

    ~TREE_QUEUE();

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

void boyer_moore(TREE_QUEUE *Q, ofstream *f_log, string file_name)
{
    while (!Q->empty())
    {
        for (int i = 0; i < Q->top()->tree_data.f_name.length(); i++)
        {
            int j;
            for (j = 0; j < file_name.length(); j++)
            {
                if (Q->top()->tree_data.f_name[i + j] != file_name[j])
                    break;
            }
            if (j == file_name.length())
                *f_log << "\"" << Q->top()->tree_data.f_name << "\" / " << Q->top()->tree_data.index << "\n";
        }

        Q->pop();
    }
};