#ifndef QUEUE_H
#define QUEUE_H

#include "Manager.h"
#include "TreeNode.h"
#include "BinarySearchTree.h"

#define IMG_SIZE 512

template <class T>
class QUEUE
{
public:
    int head;
    int tail;
    T *tree_element;

    QUEUE()
    {
        head = 0;
        tail = 0;
        tree_element = new T[IMG_SIZE * IMG_SIZE];
    };

    ~QUEUE()
    {
        delete[] tree_element;
    };

    void push(T tmp)
    {
        tree_element[tail++] = tmp;
    }

    void pop(void)
    {
        head++;
    }

    T top(void)
    {
        return (tree_element[head]);
    }

    bool empty(void)
    {
        return (tail == head);
    }
};

void boyer_moore(QUEUE<Database_BST_Node> *Q, ofstream *f_log, string file_name)
{
    while (!Q->empty())
    {
        for (unsigned int i = 0; i < Q->top().tree_data->file_name.length(); i++)
        {
            unsigned int j;
            for (j = 0; j < file_name.length(); j++)
            {
                if (Q->top().tree_data->file_name[i + j] != file_name[j])
                    break;
            }
            if (j == file_name.length())
                *f_log << "\"" << Q->top().tree_data->file_name << "\" / " << Q->top().tree_data->index << "\n";
        }
        Q->pop();
    }
};

#endif