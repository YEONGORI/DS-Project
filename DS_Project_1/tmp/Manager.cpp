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

    while (!fin.eof())
    {
        //Read the command
        fin.getline(cmd, 100);
        char* tmp = strtok(cmd, " ");
        if (strcmp(tmp, "LOAD") == 0)
        {
             Loaded_LIST* data = new Loaded_LIST;


            fout << "=========LOAD=========" << endl;
            if(!fdata){
                ferr<<"========ERROR========\n300\n===================="<<endl;
                return;
            }

            while (!fdata.eof())
            {
                char raw1[100], raw2[100];
                
                fdata.getline(raw1, sizeof(raw1), ',');
                fdata.getline(raw2, sizeof(raw2) , '\n');

                string r1 = raw1;
                string r2 = raw2;                
            
                if(data->size >= 100){
                    data->QueuePop();
                    cout<<"check"<<endl;                   
                }
                data->QueuePush(r2, "images", r1);
                cout<<r1<<r2<<endl;
                
            }
        }
        else if (strcmp(tmp, "ADD") == 0)
        {
            Loaded_LIST* new_data = new Loaded_LIST;

            data->LIST_push(new_data);

            char path[100] = {'\0'};
            char* tmp2 = strtok(NULL, " ");
            char* tmp3 = strtok(NULL, " ");
            strcat(path, tmp2);
            strcat(path, "/");
            strcat(path, tmp3);
            // cout << "path: " << path << '\n';
            ndata.open(path);
            while (!ndata.eof())
            {
                char raw1[100], raw2[100];
                
                fdata.getline(raw1, sizeof(raw1), ',');
                fdata.getline(raw2, sizeof(raw2) , '\n');

                string r1 = raw1;
                string r2 = raw2;                
            
                // if(data->size >= 100){
                //     data->QueuePop();
                //     cout<<"check"<<endl;                   
                // }
                // data->QueuePush(r2, "images", r1);
                // cout<<r1<<r2<<endl;
                
            }
        }
    }

    // TODO: implement
}


