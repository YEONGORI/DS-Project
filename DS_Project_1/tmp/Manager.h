#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include <fstream>
#include <cstring>
#include <string>

class Node
{
private:
    string file_name;
    string dir_name;
    int number;
};

class Loaded_LIST
{
private:
    Node *first;
    Node *last;
public:
    Loaded_LIST(void);
    virtual ~Loaded_LIST();

    void QueuePush(Node data);
    void QueuePop(void);
    void StackPush(Node data);
    void StackPop(void);
    
    bool isEmpty(void);
    void Print(void);
};

class Manager
{
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt";
    

    std::ofstream fout;
    std::ofstream ferr;
    std::ifstream fin;
    std::ifstream fdata;
public:
    ~Manager();
    void Run(const char* filepath);
};

#endif
