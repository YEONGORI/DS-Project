#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include <fstream>

class Manager
{
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt";
    

    std::ofstream fout;
    std::ofstream ferr;
    std::ifstream fin;
    std::ifstream fdata;
public:
    ~Manager();
    void Run(const char* filepath);


private:


};

#endif
