#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"
class BpTreeDataNode : public BpTreeNode
{
public:
	multimap<int, FrequentPatternNode *> mapData;
	BpTreeNode *pNext;
	BpTreeNode *pPrev;
	BpTreeDataNode()
	{

		pNext = nullptr;
		pPrev = nullptr;
	}

	void setNext(BpTreeNode *pN) { pNext = pN; }
	void setPrev(BpTreeNode *pN) { pPrev = pN; }
	BpTreeNode *getNext() { return pNext; }
	BpTreeNode *getPrev() { return pPrev; }

	void insertDataMap(int n, FrequentPatternNode *pN)
	{
		mapData.insert(map<int, FrequentPatternNode *>::value_type(n, pN));
	}

	void deleteMap(int n)
	{
		mapData.erase(n);
	}
	multimap<int, FrequentPatternNode *> *getDataMap() { return &mapData; }
};

#endif
