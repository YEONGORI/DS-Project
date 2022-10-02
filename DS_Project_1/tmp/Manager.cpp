#include "Manager.h"
#include <cstring>
#include <iostream>

using namespace std;

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();

    if (ferr.is_open())
        ferr.close();
}

void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH);
    ferr.open(RESULT_LOG_PATH);
    fin.open("command.txt");
    fdata.open("filesnumbers.csv");

    char cmd[100];

    Loaded_LIST* LIST = new Loaded_LIST;

    while (!fin.eof())
    {
        //Read the command
        fin.getline(cmd, 100);
        char* tmp = strtok(cmd, " ");
        if (strcmp(tmp, "LOAD") == 0)
        {
            ROW_LIST * R_LIST = new ROW_LIST;

            fout << "=========LOAD=========" << endl;
            if(!fdata){
                ferr<<"========ERROR========\n100\n===================="<<endl;
                return;
            }

            while (!fdata.eof())
            {
                char raw1[100], raw2[100];
                
                if (!fdata.getline(raw1, sizeof(raw1), ','))
                    break;
                fdata.getline(raw2, sizeof(raw2) , '\n');
                string r1 = raw1; // r1 = 고유번호
                string r2 = raw2; // 파일 이름
                if (R_LIST->size >= 100){
                    R_LIST->QueuePop();
                    cout<<"check"<<endl;                   
                }
                R_LIST->QueuePush(r2, "images", r1);
            }
            LIST->QueuePush(R_LIST);

        }
        else if (strcmp(tmp, "ADD") == 0)
        {
            ROW_LIST* rowlist = new ROW_LIST;

            char path[100] = {0};
            char* tmp2 = strtok(NULL, " ");
            char* tmp3 = strtok(NULL, " ");
            strcat(path, tmp2);
            strcat(path, "/");
            strcat(path, tmp3);

            int i;
            for (i=0;path[i];i++);
            path[i-1] = 0;

            ndata.open(path);

            while (!ndata.eof())
            {
                char raw1[100], raw2[100];
                
                if (!ndata.getline(raw1, sizeof(raw1), ','))
                    break;
                ndata.getline(raw2, sizeof(raw2) , '\n');

                string r1 = raw1;
                string r2 = raw2;           
                
                if (rowlist->size >= 100){
                    rowlist->QueuePop();
                    
                }
                rowlist->QueuePush(r2, "images", r1);              
            }
            LIST->QueuePush(rowlist);
            while(1);
            
        }

         else if (strcmp(tmp, "MODIFY") == 0)
        {
            char* tmp2 = strtok(NULL, " "); //dir
            char* tmp3 = strtok(NULL, " "); //file
            char* tmp4 = strtok(NULL, " "); //index


        }
    }

    // TODO: implement
}






            /*Node* current = data->ff_first;

            while(tmp2 != current->dir_name){
                current = current->down;
            }
            while(tmp3 != current->file_name){
                current = current->back;
            }

            if(current == NULL){
                cout<< "없음"<<endl;
            }

            if(current->up != NULL){
                current->back->up = current->up;
                current->back->down = current->down;

                current->up->down = current->back;
                current->down->up = current->back;
                
            }
            else {
                current->back->front = current->front;
                current->front->back = current->back;
                delete current;
            }

            char* tmp2 = strtok(NULL, " "); //dir
            char* tmp3 = strtok(NULL, " "); //file
            char* tmp4 = strtok(NULL, " "); //index
            data->QueuePush(, "images", r1);
            //push
            data-*/