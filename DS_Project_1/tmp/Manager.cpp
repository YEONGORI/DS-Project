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
                int index;
                string raw;
                fdata >> index;
                fdata >> raw;
                cout << index << raw << endl;
            }


        }

    }

    // TODO: implement
}


