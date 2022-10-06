#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif

#include "Manager.h"
#include "TreeNode.h"

// This stack is Refernce code (Do Not Use directly)



/*
class Stack
{
private:
    class StackNode
    {
    public:
        T Data;
        StackNode* pNext;

        StackNode(T data) : Data(data), pNext(NULL) {}
    };

private:
    // the head pointer of the stack and queue
    StackNode* m_pTop;

public:
    Stack();
    ~Stack();

    /// <summary>
    /// push the data into this stack and queue
    /// </summary>
    ///
    /// <param name="data">
    /// a data to push into this stack and queue
    /// </param>
    void Push(T data);
    /// <summary>
    /// pop(remove) the last-in data from this stack and queue
    /// </summary>
    void Pop();
    /// <summary>
    /// get the last-in data of this stack and queue
    /// </summary>
    /// 
    /// <returns>
    /// the last-in data of this stack and queue
    /// </returns>
    T Top();
    /// <summary>
    /// check whether this stack and queue is empty or not.
    /// </summary>
    ///
    /// <returns>
    /// true if this stack and queue is empty.
    /// false otherwise.
    /// </returns>
    bool IsEmpty();
};*/


class MiniStack
{
public:
    int pos;
    TreeNode* dat[500];

    MiniStack() {
        pos = 0;
        //TreeNode treenode[500];
        /*for (int i = 0; i < 500; i++) {
            dat[i] = new TreeNode(NULL,NULL, NULL);
        }*/
    }
    ~MiniStack()
    {
        delete[] dat;
    }

    void push(TreeNode* tmp) {
        dat[pos++] = tmp;
    }

    void pop(void) {
        if (pos > 0)
            pos--;
    }

    TreeNode* peek() {
        return dat[pos - 1];
    }

    int empty(void) {
        return pos == 0;
    }
};

#endif
