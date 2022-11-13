#pragma once
#include "FPNode.h"
#include <list>
#include <string>

class HeaderTable
{
public:
	list<pair<int, string> > indexTable;
	map<string, FPNode*> dataTable;
	HeaderTable() { }
	~HeaderTable();
	void insertTable(string item, int frequency);
	void insertDataTable(string item, FPNode *fp);
	list<pair<int, string> > getindexTable() { return indexTable; }
	map<string, FPNode*> getdataTable() { return dataTable; }
	FPNode* getNode(string item) { return dataTable.find(item)->second; }
	void descendingIndexTable() { indexTable.sort(greater<pair<int, string> >()); }
	void ascendingIndexTable() { indexTable.sort(); }
	int find_frequency(string item);
};


