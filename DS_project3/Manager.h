#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager
{
private:
	int load;
	Graph *graph;
	vector<int> value_checker;

public:
	ofstream fout;
	Manager();
	~Manager();

	void run(const char *command_txt);

	bool LOAD(char *filename);
	bool PRINT(ofstream &out);

	bool mBFS(int vertex, ofstream &fout);
	bool mDFS_R(int vertex, ofstream &fout);
	bool mDFS(int vertex, ofstream &fout);
	bool mDIJKSTRA(int vertex, ofstream &fout);
	bool mKRUSKAL(ofstream &fout);
	bool mBELLMANFORD(int s_vertex, int e_vertex, ofstream &fout);
	bool mFLOYD(ofstream &fout);

	void printSuccessCode(void);
	void printErrorCode(int n);
};

#endif