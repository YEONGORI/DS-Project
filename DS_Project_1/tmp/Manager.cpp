#include "Manager.h"
#include <cstring>
#include <iostream>
#include <strings.h>

using namespace std;

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();
}

void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH);
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
                fout<<"========ERROR========\n100\n===================="<<endl;
                break;;
            }

            while (!fdata.eof())
            {
                char buffer[100];
                bzero(buffer, sizeof(buffer));
                char* raw1, *raw2;
                
                if (!fdata.getline(buffer, sizeof(buffer)))
                    break;
                raw1 = strtok(buffer, ",");
                raw2 = strtok(NULL, "\n");
                
                int i;
                for(i=0;raw2[i];i++);
                raw2[i-1] = '\0';

                string r1 = raw1; // r1 = 고유번호
                string r2 = raw2; // 파일 이름
                if (R_LIST->size >= 100){
                    R_LIST->QueuePop();
                    cout<<"check"<<endl;                   
                }
                R_LIST->QueuePush(r2, "images", r1);
                fout<<r2<<"/";
                fout<<r1<< endl;
            }
            LIST->QueuePush(R_LIST);

            fout<<"=================\n"<<endl;

        }
        else if (strcmp(tmp, "ADD") == 0)
        {
            ROW_LIST* rowlist = new ROW_LIST;

            char path[100] = {0};
            char* dir = strtok(NULL, " ");
            char* file = strtok(NULL, " ");
            if (dir == NULL || file == NULL)
            {
                fout<<"========ERROR========\n200\n====================\n"<<endl;
            }
            strcat(path, dir);
            strcat(path, "/");
            strcat(path, file);

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
                if (LIST->isEmpty()) {
                    fout<<"========ERROR========\n200\n====================\n"<<endl;
                }
                rowlist->QueuePush(r2, dir, r1);              
            }
            LIST->QueuePush(rowlist);
            fout<<"=======ADD========\nSUCCESS\n===================\n"<<endl;                   
        }
        else if (strcmp(tmp, "MODIFY") == 0)
        {
            char* dir = strtok(NULL, " "); //dir
            char* file = strtok(NULL, "\""); //file
            char* index = strtok(NULL, " "); //index
            if (dir == NULL || file == NULL || index == NULL)
            {
                fout<<"========ERROR========\n300\n====================\n"<<endl;
                break;
            }
            Node* curNode = LIST->start_list->first;
            ROW_LIST* curRowList = LIST->start_list;
            bool dir_case = false;
            bool file_case = false;
            while (curNode->dir != dir)
            {
                curRowList = curRowList->down;               
                if ( curRowList == NULL){
                    fout<<"========ERROR========\n300\n====================\n"<<endl;
                    dir_case = true;
                    break;
                }
                curNode = curRowList->first;
                
            }
            if(dir_case)
                continue;
            while (curNode->file != file)
            {                
                curNode = curNode->back;              
                if (curNode == NULL)
                {
                    fout<<"========ERROR========\n300\n====================\n"<<endl;
                    file_case = true;
                    break;
                }
            }
            if(file_case)
                continue;            
            Node* frontNode;
            Node* backNode;
            frontNode = curNode->front;
            backNode = curNode->back;
            frontNode->back = backNode;
            backNode->front = frontNode;
            delete curNode;
            curRowList->QueuePush(file, dir, index);       
            fout<<"=======MODIFY========\nSUCCESS\n====================\n"<<endl;  
        }
    }

    // TODO: implement
}
