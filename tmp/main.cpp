// Implement code on Manager.c file (recommandation)
#include <cstring>
#include <list>
#include <string>
#include <iostream>
#include "Manager.h"

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    const char *commandFilepath = "command.txt";
    if (argc > 1)
        commandFilepath = argv[1];

    Manager m;
    m.Run(commandFilepath);

    return 0;
}