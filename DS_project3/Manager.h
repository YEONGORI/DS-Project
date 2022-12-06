#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager
{
private:
	Graph *graph;
	int load;

public:
	ofstream fout;
	Manager();
	~Manager();

	void run(const char *command_txt);

	bool LOAD(char *filename);
	bool PRINT();

	bool mBFS(int vertex);
	bool mDFS_R(int vertex);
	bool mDFS(int vertex);
	bool mDIJKSTRA(int vertex);
	bool mKRUSKAL();
	bool mBELLMANFORD(int s_vertex, int e_vertex);
	bool mFLOYD();

	void printSuccessCode(void);
	void printErrorCode(int n);
};

#endif