#include "Manager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

#define BUFF_SIZE 128

using namespace std;

void Manager::run(const char* command)
{
	fin.open(command);
	fmarket.open("market.txt");
	if(!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
	char cmd[BUFF_SIZE] = {};

	while (!fin.eof())
	{
		fin.getline(cmd, BUFF_SIZE);
		char *tmp = strtok(cmd, " ");
        char *ch_cr = strrchr(tmp, 13);
        if (ch_cr)
            *ch_cr = 0;
		vector<pair<string, int> > V;
        if (strcmp(tmp, "LOAD") == 0)
        {
            while (!fmarket.eof())
            {
                char buff[BUFF_SIZE];
                string index, file_name;

				vector<vector<string> > v2;
				vector<string> v1;
                if (!fmarket.getline(buff, sizeof(buff)))
                    break;
				string tmp;
				while (strtok(buff, "\t")){
					v1.push_back(buff);
				}
				v2.push_back(v1);
			}

			while(1);


                // index = strtok(buff, "\t");

                // if (NEW_LIST->edge_left == NULL)
                //     index = index.substr(3, index.size());
                // if (list_size > 100)
                // {
                //     NEW_LIST->PopNode();
                //     list_size--;
                // }

                // NEW_LIST->PushNode(file_name, "img_files", index);
                // list_size++;
                // f_log << file_name << "/" << index << '\n';
            // }



			// string tmp;
			// fin >> tmp;

			// vector<pair<string, int> >::iterator it = find(V.begin(), V.end(), tmp);
			// if (it == V.end()) // 해당원소없음
			// 	V.push_back(make_pair(tmp, 0));
			// else // 해당원소존재
			// 	it->second++;
		}

	}
	fin.close();
	return;
}

bool Manager::LOAD()
{
	return true;
}




// bool Manager::BTLOAD()
// {
	
// 	return true;
// }

// bool Manager::PRINT_ITEMLIST() {
	
// }

// bool Manager::PRINT_FPTREE() {
	
// }

// bool Manager::PRINT_BPTREE(char* item, int min_frequency) {
	
// }

// bool Manager::PRINT_CONFIDENCE(char* item, double rate) {
	
// }

// bool Manager::PRINT_RANGE(char* item, int start, int end) {
	
// }

// void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
// 	// flog << ERROR " << n << " << endl;
// 	flog << "=======================" << endl << endl;
// }

// void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
// 	flog << "Success" << endl;
// 	flog << "=======================" << endl << endl;
// }

