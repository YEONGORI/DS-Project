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
    friend class Middle_LIST;
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
    Node(string file_name, string dir_name, string number, Node *fron, Node *back):file_name(file_name), dir_name(dir_name), number(number), front(front) , back(back) {}
};

class Loaded_LIST
{
private:
    Middle_LIST *first;
    Middle_LIST *last;
public:
    int size;
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

    void QueuePush(string file, string dir, string index){
        // last = last->front = new Node(data.file_name, data.dir_name, data.number, NULL);
        // O <-> O <-> O
        if (isEmpty())
            first = last = new Node(file, dir, index, NULL , NULL);
        else {
            Node* Node_tmp = new Node(file, dir, index, NULL , NULL);
            first->front = Node_tmp;
            Node_tmp->back = first;
            first = Node_tmp;
        }
        size++;
    }
    void QueuePop(void){
        Node* end = last;
        if(isEmpty()){
            cout<<"queuepop:empty"<<endl;
        }
        else {
            cout<<"queuepop: "<<end->number<<endl;
            last = last->front;
            last->back = NULL;
            delete end;
        }
        size--;
    }
    void StackPush(string file, string dir, string index){
        if (isEmpty())
            first = last = new Node(file, dir, index, NULL , NULL);
        else {
            Node* Node_tmp = new Node(file, dir, index, NULL , NULL);
            first->front = Node_tmp;
            Node_tmp->back = first;
            first = Node_tmp;
        }
        size++;
    }
    void StackPop(void){
        Node* top = first;
        if(isEmpty()){
            cout<<"StackPop: empty" <<endl;
        }
        else{
            cout<< "StackPop: "<<top->number<<endl;
            first = first->back;
            first->front = NULL;
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
// O <-> 로디드리스트
// ^
// O <-> O <-> O 미들 리스트

class Middle_LIST
{
private:
    Node *first;
    Node *last;
    Node *up;
    Node *down;
    
public:
    int size;
    Middle_LIST(void){
        first = NULL;
        last = NULL;
        size = 0;
    }
    virtual ~Middle_LIST(){
        Node* front = NULL;

        while(first != NULL){
            front = first->front;
            delete first;
            first = front;
        }
    }

    void QueuePush(string file, string dir, string index){
        // last = last->front = new Node(data.file_name, data.dir_name, data.number, NULL);
        // O <-> O <-> O
        if (isEmpty())
            first = last = new Node(file, dir, index, NULL , NULL);
        else {
            Node* Node_tmp = new Node(file, dir, index, NULL , NULL);
            first->front = Node_tmp;
            Node_tmp->back = first;
            first = Node_tmp;
        }
        size++;
    }
    void QueuePop(void){
        Node* end = last;
        if(isEmpty()){
            cout<<"queuepop:empty"<<endl;
        }
        else {
            cout<<"queuepop: "<<end->number<<endl;
            last = last->front;
            last->back = NULL;
            delete end;
        }
        size--;
    }
    void StackPush(string file, string dir, string index){
        if (isEmpty())
            first = last = new Node(file, dir, index, NULL , NULL);
        else {
            Node* Node_tmp = new Node(file, dir, index, NULL , NULL);
            first->front = Node_tmp;
            Node_tmp->back = first;
            first = Node_tmp;
        }
        size++;
    }
    void StackPop(void){
        Node* top = first;
        if(isEmpty()){
            cout<<"StackPop: empty" <<endl;
        }
        else{
            cout<< "StackPop: "<<top->number<<endl;
            first = first->back;
            first->front = NULL;
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
    std::ifstream ndata;
public:
    ~Manager();
    void Run(const char* filepath);
};

#endif
