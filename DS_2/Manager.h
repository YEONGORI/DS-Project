#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
// #include "FPGrowth.h"
// #include "BpTree.h"

using namespace std;

class Manager
{
private:
	char* cmd;
	// FPGrowth* fpgrowth;
	// BpTree* bptree;
public:
	Manager(int threshold, int bpOrder)	//constructor
	{
		/* You must fill here */
	}


	~Manager()//destructor
	{
		/* You must fill here */
	}

	ifstream fin;
	ifstream fmarket;
	ofstream flog;
	

	void run(const char* command);
	bool LOAD();
	bool BTLOAD();
	
	bool PRINT_ITEMLIST();
	bool PRINT_FPTREE();

	bool PRINT_RANGE(char* item, int start, int end);
	bool PRINT_CONFIDENCE(char* item, double rate);
	bool PRINT_BPTREE(char* item, int min_frequency);


	void printErrorCode(int n);
	void printSuccessCode();

};

