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
                char* raw1;
                char* raw2;
                raw1 = new char[100];
                raw2 = new char[100];
                fdata.getline(raw1, sizeof(raw1), ',');
                fdata.getline(raw2, sizeof(raw2) , '\n');
                char* images = "images";
                Node tmp(raw2, images, raw1, NULL);
                
                data->StackPush();
            }
        }
    }

    // TODO: implement
}


