#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"
class BpTreeDataNode : public BpTreeNode
{
private:
	map<string, VaccinationData *> mapData;
	BpTreeNode *pNext;
	BpTreeNode *pPrev;

public:
	BpTreeDataNode() // constructor
	{
		pNext = nullptr;
		pPrev = nullptr;
	}
	~BpTreeDataNode() // destructor
	{
		mapData.clear();
		pNext = nullptr;
		pPrev = nullptr;
	}
	// setter
	void setNext(BpTreeNode *pN) { pNext = pN; }
	void setPrev(BpTreeNode *pN) { pPrev = pN; }
	// getter
	BpTreeNode *getNext() { return pNext; }
	BpTreeNode *getPrev() { return pPrev; }

	// insert the data in data map
	void insertDataMap(string n, VaccinationData *pN)
	{
		mapData.insert(map<string, VaccinationData *>::value_type(n, pN));
	}
	// delete data in map
	void deleteMap(string n)
	{
		mapData.erase(n);
	}
	map<string, VaccinationData *> *getDataMap() { return &mapData; }
};

#endif