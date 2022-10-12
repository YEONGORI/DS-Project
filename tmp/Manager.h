#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "TreeNode.h"

using namespace std;

class Node
{
public:
    string file_name;
    string dir_name;
    string index;

    Node *prev;
    Node *next;

    Node(string file_name, string dir_name, string index, Node *prev, Node *next) :
    file_name(file_name), dir_name(dir_name), index(index), prev(prev), next(next) {}
};

class ROW_LIST
{
public:
    int size;

    Node *edge_right;
    Node *edge_left;

    ROW_LIST *go_up;
    ROW_LIST *go_down;

    ROW_LIST(void)
    {
        size = 0;
        edge_right = NULL;
        edge_left = NULL;
        go_up = NULL;
        go_down = NULL;
    };

    ~ROW_LIST()
    {
        Node *next = NULL;

        while (edge_left != NULL)
        {
            next = edge_left->next;
            delete edge_left;
            edge_left = next;
        }
    }

    void PushNode(string file_name, string dir_name, string index)
    {
        if (IsEmpty())
            edge_right = edge_left = new Node(file_name, dir_name, index, NULL, NULL);
        else
        {
            Node *next = new Node(file_name, dir_name, index, NULL, NULL);
            edge_right->next = next;
            next->prev = edge_right;
            edge_right = next;
        }
        size++;
    };

    void PopNode(void)
    {
        Node *tmp = edge_left;

        if (IsEmpty())
            cout << "EMPTY\n";
        else
        {
            edge_left = tmp->next;
            delete tmp;
            size--;
        }
    };

    bool IsEmpty(void)
    {
        return (edge_left == NULL);
    }
};

class Loaded_LIST
{
public:
    ROW_LIST *top_list;
    ROW_LIST *bottom_list;

    Loaded_LIST(void)
    {
        top_list = NULL;
        bottom_list = NULL;
    };

    ~Loaded_LIST()
    {
        ROW_LIST *next = NULL;

        while (top_list != NULL)
        {
            next = top_list->go_down;
            delete top_list;
            top_list = next;
        }
    }

    void PushList(ROW_LIST *data)
    {
        if (IsEmpty())
            top_list = bottom_list = data;
        else
        {
            bottom_list->go_down = data;
            data->go_up = bottom_list;
            bottom_list = data;
        }
    }

    bool IsEmpty(void)
    {
        return (top_list == NULL);
    }
};

class Manager
{
private:
    // the filepath for the result log
    const char *RESULT_LOG_PATH = "log.txt";

    std::ofstream f_log;
    std::ifstream f_cmd;
    std::ifstream f_file;
    std::ifstream f_new;

public:
    ~Manager();
    void Run(const char *filepath);
};

#endif