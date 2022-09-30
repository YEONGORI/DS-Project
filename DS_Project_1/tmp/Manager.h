#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include <fstream>
#include <cstring>
#include <string>

class Node
{
    friend class Loaded_LIST;
private:
    char* file_name;
    char* dir_name;
    int number;
    Node* link;
public:
    Node(char* file_name, char* dir_name, int number, Node* link): file_name(file_name), dir_name(dir_name), number(number), link(link){}

};

class Loaded_LIST
{
private:
    Node *first;
    Node *last;
public:
    Loaded_LIST(void){
        first = NULL;
        last = NULL;
    }
    virtual ~Loaded_LIST(){
        Node* next = NULL;

        while(first != NULL){
            next = first->link;
            delete first;
            first = next;
        }
    }

    void QueuePush(Node data){
        if(isEmpty()){
            first = last = new Node(data.file_name, data.dir_name, data.number, NULL);
        }
        else {
            last = last->link = new Node(data.file_name, data.dir_name, data.number, NULL);
        }
    }
    void QueuePop(void){
        Node* front = first;
        if(isEmpty()){
            cout<<"queuepop:empty"<<endl;
        }
        else {
            cout<<"queuepop"<<front->number<<endl;
            first = front->link;
            delete front;
        }
    }
    void StackPush(Node data){
        first = new Node(data.file_name, data.dir_name, data.number, first);
        cout<<"StackPush: " << data.number<<endl;
    }
    void StackPop(void){
        Node* top = first;
        if(isEmpty()){
            cout<<"StackPop: empty" <<endl;
        }
        else{
            cout<< "StackPop: "<<top->number<<endl;
            first = top->link;
            delete top;
        }
    }
    
    bool isEmpty(void){
        return first == NULL;
    }
    void Print(void){
        Node* current = first;
        cout<<"Print: ";
        while(current != NULL){
            cout<<current->number<<" ";
            current = current->link;
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
