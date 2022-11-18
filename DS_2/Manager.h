#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include "FPGrowth.h"
#include "BpTree.h"

using namespace std;

class Manager
{
private:
	char *cmd;
	int threshold;
	int bpOrder;
	FPGrowth *fpgrowth;
	BpTree *bptree;

public:
	Manager(int threshold, int bpOrder) // constructor
	{
		this->fpgrowth = new FPGrowth;
		this->bptree = new BpTree;
		this->threshold = threshold;
		this->bpOrder = bpOrder;
		bptree->root = nullptr;
		// bptree->root = NULL;
		/* You must fill here */
	}

	~Manager() // destructor
	{
		/* You must fill here */
	}

	ifstream fin;
	ifstream fmarket;
	ifstream fresult;

	ofstream fout;
	ofstream flog;

	void run(const char *command);
	bool LOAD();
	bool BTLOAD();

	bool PRINT_ITEMLIST();
	bool PRINT_FPTREE();

	bool PRINT_RANGE(char *item, int start, int end);
	bool PRINT_CONFIDENCE(char *item, double rate);
	bool PRINT_BPTREE(char *item, int min_frequency);

	void printErrorCode(int n);
	void printSuccessCode();
};
