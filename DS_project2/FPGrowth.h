#pragma once
#include <set>
#include <vector>
#include <fstream>
#include <iostream>

#include "HeaderTable.h"

class FPGrowth
{
public:
	int threshold;

	FPNode *fpTree;
	HeaderTable *table;
	map<set<string>, int> frequenctPatterns;

	ofstream flog;

	FPGrowth()
	{
		fpTree = new FPNode;
		table = new HeaderTable;
	}

	FPGrowth(ofstream *fout, int threshold = 3)
	{
		this->threshold = threshold;
		flog.open("result.txt", ios::app);
		flog.setf(ios::fixed);
		fpTree = new FPNode;
		table = new HeaderTable;
	}
	~FPGrowth();

	void createFPtree(FPNode *root, HeaderTable *table, vector<vector<string>> total_item);
	void createTable(string item, int frequency)
	{
		table->insertTable(item, frequency);
	}
	void connectNode(HeaderTable *table, string item, FPNode *node);

	void frequenctPatternSetting()
	{
		table->ascendingIndexTable();
		frequenctPatterns = getFrequentPatterns(table, fpTree);
	}

	map<set<string>, int> getFrequentPatterns(HeaderTable *pTable, FPNode *pTree);
	void powerSet(map<set<string>, int> *FrequentPattern, vector<string> data, string item, int frequency, int *flag, int depth);
	bool contains_single_path(FPNode *pNode);
	int item_frequency(string item) { return table->find_frequency(item); }
	FPNode *getTree() { return fpTree; }
	HeaderTable *getHeaderTable() { return table; }

	bool printList();
	bool printTree();
	void saveFrequentPatterns();
};
