#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"
class BpTreeIndexNode : public BpTreeNode
{
private:
	map<string, BpTreeNode *> mapIndex;

public:
	BpTreeIndexNode() {}					 //constructor
	~BpTreeIndexNode() { mapIndex.clear(); } //destructor

	//inset data in index map
	void insertIndexMap(string n, BpTreeNode *pN)
	{
		mapIndex.insert(map<string, BpTreeNode *>::value_type(n, pN));
	}
	//delete data in map
	void deleteMap(string n)
	{
		mapIndex.erase(n);
	}

	map<string, BpTreeNode *> *getIndexMap() { return &mapIndex; }
};

#endif