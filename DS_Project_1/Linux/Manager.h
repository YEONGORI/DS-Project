#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "TreeNode.h"

using namespace std;

class Loaded_LIST_Node
{
public:
    string file_name;
    string dir_name;
    string index;

    Loaded_LIST_Node *prev;
    Loaded_LIST_Node *next;

    Loaded_LIST_Node(string file_name, string dir_name, string index, Loaded_LIST_Node *prev, Loaded_LIST_Node *next) :
    file_name(file_name), dir_name(dir_name), index(index), prev(prev), next(next) {}
};

class ROW_LIST
{
public:
    Loaded_LIST_Node *edge_right;
    Loaded_LIST_Node *edge_left;

    ROW_LIST *go_up;
    ROW_LIST *go_down;

    ROW_LIST(void)
    {
        edge_right = NULL;
        edge_left = NULL;
        go_up = NULL;
        go_down = NULL;
    };

    ~ROW_LIST() {};

    void PushNode(string file_name, string dir_name, string index)
    {
        if (edge_left == NULL)
            edge_right = edge_left = new Loaded_LIST_Node(file_name, dir_name, index, NULL, NULL);
        else
        {
            Loaded_LIST_Node *next = new Loaded_LIST_Node(file_name, dir_name, index, NULL, NULL);
            edge_right->next = next;
            next->prev = edge_right;
            edge_right = next;
        }
    };

    void PopNode(void)
    {
        if (!(edge_left == NULL))
        {
            Loaded_LIST_Node *tmp = edge_left;

            edge_left = tmp->next;
            delete tmp;
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

    ~Loaded_LIST() {};

    void PushList(ROW_LIST *data)
    {
        if (top_list == NULL)
            top_list = bottom_list = data;
        else
        {
            bottom_list->go_down = data;
            data->go_up = bottom_list;
            bottom_list = data;
        }
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