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

    Loaded_LIST* data = new Loaded_LIST;

    char cmd[100];

    while (!fin.eof())
    {
        //Read the command
        fin.getline(cmd, 100);
        char* tmp = strtok(cmd, " ");
        if (strcmp(tmp, "LOAD") == 0)
        {
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
    }

    // TODO: implement
}


