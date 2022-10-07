#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include <fstream>
#include <cstring>
#include <string>
#include <iostream>
#include "TreeNode.h"

using namespace std;

class Node
{
public:
    string file;
    string dir;
    string number;
    Node *front;
    Node *back;
    Node(string file, string dir, string number, Node *front, Node *back) : file(file), dir(dir), number(number), front(front), back(back) {}
};

class ROW_LIST
{
public:
    int size;
    Node *last;
    Node *first;
    ROW_LIST *up;
    ROW_LIST *down;

    ROW_LIST(void)
    {
        size = 0;
        last = NULL;
        first = NULL;
        up = NULL;
        down = NULL;
    };
    ~ROW_LIST(void)
    {
        Node *next = NULL;

        while (first != NULL)
        {
            next = first->back;
            cout << "DELETE: " << first->back << endl;
            delete first;
            first = next;
        }
    }

    void QueuePush(string file, string dir, string index)
    {
        if (isEmpty())
            last = first = new Node(file, dir, index, NULL, NULL);
        else
        {
            // O - O [ - O ]
            Node *next = new Node(file, dir, index, NULL, NULL);
            last->back = next;
            next->front = last;
            last = next;
        }
        size++;
    };

    void QueuePop(void)
    {
        Node *front = first;
        if (isEmpty())
        {
            cout << "EMPTY\n";
        }
        else
        {
            cout << "Q pop\n";
            first = front->back;
            delete front;
            size--;
        }
    };

    void StackPop(void)
    {
        Node *end = last;
        if (isEmpty())
        {
            cout << "EMPTY\n";
        }
        else
        {
            last = end->front;
            delete end;
            size--;
        }
    }

    bool isEmpty(void)
    {
        return (last == NULL && first == NULL);
    }
};

class Loaded_LIST
{
public:
    ROW_LIST *start_list;
    ROW_LIST *end_list;

    Loaded_LIST(void)
    {

        start_list = NULL;
        end_list = NULL;
    }
    ~Loaded_LIST()
    {
        ROW_LIST *next = NULL;

        while (start_list != NULL)
        {
            next = start_list->down;
            delete start_list;
            start_list = next;
        }
    }

    // number, file, dir
    void QueuePush(ROW_LIST *data)
    {
        if (isEmpty())
        {
            start_list = end_list = data;
        }
        else
        {
            end_list->down = data;
            data->up = end_list;
            end_list = data;
        }
    }

    bool isEmpty(void)
    {
        return start_list == NULL;
    }
};

class Manager
{
private:
    // the filepath for the result log
    const char *RESULT_LOG_PATH = "log.txt";

    std::ofstream fout;
    std::ofstream fout2;
    std::ifstream fin;
    std::ifstream fdata;
    std::ifstream ndata;

public:
    ~Manager();
    void Run(const char *filepath);
};

#endif