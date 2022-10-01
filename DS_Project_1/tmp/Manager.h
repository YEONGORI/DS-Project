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
public:
    Node* front;
    Node* back;
    string dir;
    string file;
    string number;
    Node(string file,string dir,  string number, Node *front, Node *back):
    file(file), dir(dir), number(number), front(front) , back(back) {}
};

class ROW_LIST
{
public:
    int size;
    Node* last;
    Node* first;
    ROW_LIST* up;
    ROW_LIST* down;

ROW_LIST(void){
    size =0;
    last =NULL;
    first =NULL;
    up =NULL;
    down =NULL;
};
~ROW_LIST(void){
    Node* next = NULL;

    while (first !=NULL){
        next = first->back;
        cout << "DELETE: " << first->back << endl;
        delete first;
        first = next;
    }
}

void QueuePush(string file, string dir, string index){
    if (isEmpty())
        first = last = new Node(file, dir, index, NULL , NULL);
    else {
        last = last->back = new Node(file, dir, index, NULL, NULL);   
        cout << last->file << '\n';
    }
    size++;
};
void QueuePop(void){
    Node *front = first;
    if (isEmpty()){
        cout << "EMPTY\n";
    }
    else{
        cout << "Q pop\n";
        first = front->back;
        delete front;
        size--;
    }
};
void StackPop(void){
    Node* end = last;
    if (isEmpty()){
        cout << "EMPTY\n";
    }
    else{
        cout << "Q pop\n";
        last = end->front;
        delete end;
        size--;
    }
}
bool isEmpty(void){
    return first ==NULL;
}
};

class Loaded_LIST{
public:
    ROW_LIST* ft;
    ROW_LIST* lt;
    
    Loaded_LIST(void){
        
        ft = new ROW_LIST;
        lt = new ROW_LIST;
    }
    ~Loaded_LIST(){
        ROW_LIST* next = NULL;

        while(ft != NULL){
            next = ft->down;
            delete ft;
            ft = next;
        }
    }

    // number, file, dir
    void QueuePush(ROW_LIST* data){
        lt = lt->down = data;
    }

    /*void QueuePop(void){


        Node *front = first;
        if (isEmpty()){
            cout << "EMPTY\n";
        }
        else{
            cout << "Q pop\n";
            first = front->back;
            delete front;
        }
    }
void StackPop(void){
    Node* end = last;
    if (isEmpty()){
        cout << "EMPTY\n";
    }
    else{
        cout << "Q pop\n";
        last = end->front;
        delete end;
    }
}
bool isEmpty(void){
    return first ==NULL;
}*/


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


// class Node
// {
//     friend class Middle_LIST;
//     friend class Loaded_LIST;
// private: 
    
// public:
//     Node* front;
//     Node* back;
//     Node* up;
//     Node* down;
//     string file_name;
//     string dir_name;
//     string number;
//     Node(string file_name, string dir_name, string number, Node *fron, Node *back):file_name(file_name), dir_name(dir_name), number(number), front(front) , back(back), up(up), down(down) {}
// };

// class Loaded_LIST
// {
//     int size;
//     Node *first;
//     Node *last;
//     Node *ff_first;
//     Node *ll_last;
//     Loaded_LIST(void){
//         first = NULL;
//         last = NULL;
//         ff_first = NULL;
//         ll_last = NULL;
//         size = 0;
//     }
//     virtual ~Loaded_LIST(){
//         Node* front = NULL;

//         while(first != NULL){
//             front = first->front;
//             delete first;
//             first = front;
//         }
//     }
//     // 기존의 리스트
//     void LIST_push(Loaded_LIST* new_data) {
//         ll_last->down = new_data->first;
//         new_data->first->up = ll_last;
//         ll_last = new_data->first;
//     }

//     void QueuePush(string file, string dir, string index){
//         if (isEmpty())
//             first = last = new Node(file, dir, index, NULL , NULL);
//         else {
//             bool case1=false;
//             Node* Node_tmp = new Node(file, dir, index, NULL , NULL);
//             Node* curNode = first;

//             while(curNode->dir_name != dir){
//                 if(curNode->down == NULL){
//                     case1 = true;
//                     break;
//                 }
//                 curNode = curNode->down;
//             }
            
//             if(case1){
//                 curNode->down = Node_tmp;
//                 Node_tmp->up = curNode;
//             }
//             else{
//                 Node_tmp->up = curNode->up;
//                 Node_tmp->down = curNode->down;

//                 curNode->up->down = Node_tmp;
//                 curNode->down->up = Node_tmp;

//                 curNode->front = Node_tmp;
//                 Node_tmp->back = curNode;

//                 curNode->up = NULL;
//                 curNode->down = NULL;   
//             }
//         }
//         size++;
//     }
//     void QueuePop(void){
//         Node* end = last;
//         if(isEmpty()){
//             cout<<"queuepop:empty"<<endl;
//         }
//         else {
//             cout<<"queuepop: "<<end->number<<endl;
//             last = last->front;
//             last->back = NULL;
//             delete end;
//         }
//         size--;
//     }
//     void StackPush(string file, string dir, string index){
//         if (isEmpty())
//             first = last = new Node(file, dir, index, NULL , NULL);
//         else {
//             Node* Node_tmp = new Node(file, dir, index, NULL , NULL);
//             first->front = Node_tmp;
//             Node_tmp->back = first;
//             first = Node_tmp;
//         }
//         size++;
//     }
//     void StackPop(void){
//         Node* top = first;
//         if(isEmpty()){
//             cout<<"StackPop: empty" <<endl;
//         }
//         else{
//             cout<< "StackPop: "<<top->number<<endl;
//             first = first->back;
//             first->front = NULL;
//             delete top;
//         }
//         size--;
//     }
    
//     bool isEmpty(void){
//         if (first ==NULL && last==NULL && ff_first==NULL && ll_last==NULL) // 모든 리스트에 아무것도 없을 때
//             return true;
//         return false; // 로디드 리스트에 뭔가가 있을 때
//     }

//     void Print(void){
//         Node* current = first;
//         cout<<"Print: ";
//         while(current != NULL){
//             cout<<current->number<<" ";
//             current = current->front;
//         }
//         cout<<endl;
//     }
// };