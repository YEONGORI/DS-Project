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
    friend class Loaded_LIST;
private: 
    
public:
    Node* front;
    Node* back;
    Node* up;
    Node* down;
    string file_name;
    string dir_name;
    string number;
    Node(string file_name, string dir_name, string number, Node *fron, Node *back):file_name(file_name), dir_name(dir_name), number(number), front(front) , back(back), up(up), down(down) {}
};

class Loaded_LIST
{
    // O <-> O <-> O <-> O
    // |
    // O <-> O <-> O
    // |
    // O <-> O
// private:
//     Node *first;
//     Node *last;
//     Node *ff_first;
//     Node *ll_last;
public:
    int size;
    Node *first;
    Node *last;
    Node *ff_first;
    Node *ll_last;
    Loaded_LIST(void){
        first = NULL;
        last = NULL;
        ff_first = NULL;
        ll_last = NULL;
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
    // 기존의 리리스스트
    void LIST_push(Loaded_LIST* new_data) {
        ll_last->down = new_data->first;
        new_data->first->up = ll_last;
        ll_last = new_data->first;
    }

    void QueuePush(string file, string dir, string index){
        // last = last->front = new Node(data.file_name, data.dir_name, data.number, NULL);
        // O <-> O <-> O
        if (isEmpty())
            first = last = new Node(file, dir, index, NULL , NULL);
        else {
            bool case1=false;
            Node* Node_tmp = new Node(file, dir, index, NULL , NULL);
            Node* curNode = first;
            while(curNode->dir_name != dir){
                if(curNode->down == NULL){
                    case1 = true;
                    break;
                }
                curNode = curNode->down;
            }
            
            if(case1){
                curNode->down
                
            }
            else{
                Node_tmp->up = curNode->up;
                Node_tmp->down = curNode->down;

                curNode->up->down = Node_tmp;
                curNode->down->up = Node_tmp;

                curNode->front = Node_tmp;
                Node_tmp->back = curNode;

                curNode->up = NULL;
                curNode->down = NULL;   
            }
            
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
