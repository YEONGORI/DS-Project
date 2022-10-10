#ifndef QUEUE_H
#define QUEUE_H

#include "Manager.h"
#include "TreeNode.h"
#include "BinarySearchTree.h"

#define IMG_SIZE 512

class TREE_QUEUE
{
public:
    int head;
    int tail;

    TreeNode *tree_element;

    TREE_QUEUE()
    {
        head = 0;
        tail = 0;
        tree_element = new TreeNode[1000];
    };

    ~TREE_QUEUE()
    {
        delete[] tree_element;
    };

    void push(TreeNode tmp)
    {
        tree_element[tail++] = tmp;
    }

    void pop()
    {
        head++;
    }

    TreeNode top()
    {
        return (tree_element[head]);
    }

    bool empty()
    {
        return (tail == head);
    }
};

class CHAR_QUEUE
{
public:
    int head;
    int tail;
    char *char_element;

    CHAR_QUEUE()
    {
        head = 0;
        tail = 0;
        char_element = new char[IMG_SIZE * IMG_SIZE];
    };

    ~CHAR_QUEUE()
    {
        delete[] char_element;
    };

    void push(char tmp)
    {

        char_element[tail++] = tmp;
    }

    void pop()
    {
        head++;
    }

    char top()
    {
        return (char_element[head]);
    }

    bool empty()
    {
        return (tail == head);
    }
};

#endif

void boyer_moore(TREE_QUEUE *Q, ofstream *f_log, string file_name)
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