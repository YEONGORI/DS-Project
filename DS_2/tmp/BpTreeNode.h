#pragma once
#include "VaccinationData.h"
class BpTreeNode
{
private:
	BpTreeNode *pParent; //parent
	BpTreeNode *pMostLeftChild;
	int order;

public:
	BpTreeNode() //constructor
	{
		pParent = nullptr;
		pMostLeftChild = nullptr;
	}
	~BpTreeNode() //destructor
	{
		pParent = nullptr;
		pMostLeftChild = nullptr;
	}
	//setter
	void setMostLeftChild(BpTreeNode *pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode *pN) { pParent = pN; }
	//getter
	BpTreeNode *getParent() { return pParent; }
	BpTreeNode *getMostLeftChild() { return pMostLeftChild; }

	int getOrder() { return order; }
	void setOrder(int num) { order = num; }
	//---------------------------Virtual----------------------------------
	virtual void insertDataMap(string n, VaccinationData *pN) {}
	virtual void insertIndexMap(string n, BpTreeNode *pN) {}
	virtual void deleteMap(string n) {}

	virtual map<string, BpTreeNode *> *getIndexMap()
	{
		map<string, BpTreeNode *> m;
		return &m;
	}
	virtual map<string, VaccinationData *> *getDataMap()
	{
		map<string, VaccinationData *> m;
		return &m;
	}

	virtual void setNext(BpTreeNode *pN) {}
	virtual void setPrev(BpTreeNode *pN) {}
	virtual BpTreeNode *getNext() { return NULL; }
	virtual BpTreeNode *getPrev() { return NULL; }
};