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

    char cmd[32];

    while (!fin.eof())
    {
        //Read the command
        fin.getline(cmd, 32);
        char* tmp = strtok(cmd, " ");
        if (strcmp(tmp, "LOAD") == 0)
        {
            fout << "=========LOAD=========" << endl;
            while (!fdata.eof())
            {
                char raw1[100], raw2[100];
                
                fdata.getline(raw1, sizeof(raw1), ',');
                fdata.getline(raw2, sizeof(raw2) , '\n');

                string r1 = raw1;
                string r2 = raw2;
                
                Node n(r2, "images", r1, NULL);
                data->isEmpty();
                data->StackPush(n);
                data->QueuePush(n);
                data->QueuePush(n);
                data->StackPush(n);
                data->StackPush(n);
                data->QueuePop();
                data->QueuePop();
                data->StackPop();
                data->isEmpty();
                while (1);
            }
        }
    }

    // TODO: implement
}


