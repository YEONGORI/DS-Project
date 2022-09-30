#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include <fstream>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

class Node
{
    friend class Loaded_LIST;
private:
    string file_name;
    string dir_name;
    string number;
    Node* front;
    Node* back;
public:
    // Node(string file_name, string dir_name, int number, Node* front, Node * back)
    // {
    //     this->file_name = file_name;
    //     this->dir_name = dir_name;
    //     this->number = number;
    //     this->front = front;
    //     this->back = back;
    // }
    Node(string file_name, string dir_name, string number, Node *back):file_name(file_name), dir_name(dir_name), number(number), back(back) {}
};

class Loaded_LIST
{
private:
    Node *first;
    Node *last;
    int size;
public:
    Loaded_LIST(void){
        first = NULL;
        last = NULL;
        size = 0;
    }
    virtual ~Loaded_LIST(){
        Node* front = NULL;

        while(first != NULL){
            front = first->front;
            delete first;
            first = front;
        }
    }

    void QueuePush(Node data){
        // last = last->front = new Node(data.file_name, data.dir_name, data.number, NULL);
        // O <-> O <-> O
        if (isEmpty())
            first = last = new Node(data.file_name, data.dir_name, data.number, NULL, NULL);
        else {
            first->front = data;
            first = new Node(data.file_name, data.dir_name, data.number, NULL, first);
        }
        size++;
    }
    void QueuePop(void){
        Node* end = last;
        if(isEmpty()){
            cout<<"queuepop:empty"<<endl;
        }
        else {
            cout<<"queuepop"<<end->number<<endl;
            last = end->front;
            delete end;
        }
        size--;
    }
    void StackPush(Node data){
        first = new Node(data.file_name, data.dir_name, data.number, NULL, first->back);
        O <-> O <-> O <->
        O.front
        cout<<"StackPush: " << data.number<<endl;
        size++;
    }
    void StackPop(void){
        Node* top = first;
        if(isEmpty()){
            cout<<"StackPop: empty" <<endl;
        }
        else{
            cout<< "StackPop: "<<top->number<<endl;
            first = top->front;
            delete top;
        }
        size--;
    }
    
    bool isEmpty(void){
        if (first == NULL)
            cout << "ET size: " << size << '\n';
        else
            cout << "NET size: " << size << '\n';
        return first == NULL;
    }
    void Print(void){
        Node* current = first;
        cout<<"Print: ";
        while(current != NULL){
            cout<<current->number<<" ";
            current = current->front;
        }
        cout<<endl;
    }
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
