#include "Manager.h"
#include <cstring>
#include <iostream>
#include <strings.h>

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
                break;;
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
            if (tmp2 == NULL || tmp3 == NULL)
            {
                ferr<<"========ERROR========\n200\n===================="<<endl;
            }
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
                if (LIST->isEmpty()) {
                    ferr<<"========ERROR========\n200\n===================="<<endl;
                }
                rowlist->QueuePush(r2, "images", r1);              
            }
            LIST->QueuePush(rowlist);
            
        }
        else if (strcmp(tmp, "MODIFY") == 0)
        {
            char* dir = strtok(NULL, " "); //dir
            char* file = strtok(NULL, "\""); //file
            char* index = strtok(NULL, " "); //index
            if (dir == NULL || file == NULL || index == NULL)
            {
                ferr<<"========ERROR========\n300\n===================="<<endl;
                break;
            }

            Node* curNode = LIST->start_list->first;
            ROW_LIST* curRowList = LIST->start_list;
            while (curNode->dir != dir)
            {
                if (curNode == NULL || curRowList == NULL)
                {
                    ferr<<"========ERROR========\n300\n===================="<<endl;
                    break;
                }
                curRowList = curRowList->down;
                if (curRowList == NULL)
                    break;
                curNode = curRowList->first;
            }
                while(1);
            while (curNode->file != file)
            {
                curNode = curNode->back;
                if (curNode == NULL)
                {
                    ferr<<"========ERROR========\n300\n===================="<<endl;
                    break;
                }
            }
            Node* frontNode;
            Node* backNode;
            frontNode = curNode->front;
            backNode = curNode->back;
            frontNode->back = backNode;
            backNode->front = frontNode;
            delete curNode;
            curRowList->QueuePush(file, dir, index);
            cout << curRowList->last->number << "&\n";
            cout << LIST->end_list->last->number << "*\n";
        }
    }

    // TODO: implement
}
