#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeNode.h"
#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "VaccinationData.h"
// BpTree

class BpTree
{
private:
	BpTreeNode *root;
	int order;		// m children
	bool over;		// over flag
	bool done;		// done flag : check complete vaccination
	bool AddOp;		// addop flag
	bool duplicate; // duplicate flag

public:
	BpTree(int order = 3) // constructor
	{
		root = NULL;
		over = false;
		done = false;
		AddOp = false;
		duplicate = false;
		this->order = order;
	}
	~BpTree() // destructor
	{
		delete_all(root); // delete all data in bptree
		root = NULL;
	}
	// getter and setter
	BpTreeNode *getRoot() { return root; }
	bool getDone() { return done; }
	void setDone(bool s) { done = s; }
	bool getAddOp() { return AddOp; }
	void setAddOp(bool s) { AddOp = s; }
	bool getOver() { return over; }
	void setOver(bool s) { over = s; }
	bool getDuplicate() { return duplicate; }
	void setDuplicate(bool s) { duplicate = s; } // set duplicate flag's status

	bool Insert(VaccinationData *newData);		  // insert data
	bool exceedDataNode(BpTreeNode *pDataNode);	  // check whether datanode's size is 3 or not
	bool exceedIndexNode(BpTreeNode *pIndexNode); // check whether indexnode's size is 3 or not
	void splitDataNode(BpTreeNode *pDataNode);	  // split data node
	void splitIndexNode(BpTreeNode *pIndexNode);  // split index node
	BpTreeNode *searchDataNode(string n);		  // search data in bptree
	void SearchRange(string start, string end);	  // search data in range
	void Print();								  // print all data

	BpTreeNode *Find_Root(BpTreeNode *bpNode, string name) // find place that input the dat
	{
		if (!bpNode->getMostLeftChild())
		{
			return bpNode;
		}
		else
		{
			string target = bpNode->getIndexMap()->begin()->first;
			auto end = bpNode->getIndexMap()->end();
			end--;
			if (name > target || target == name) // if name is same or bigger than targer
			{
				BpTreeNode *sec;
				if (name > end->first || name == end->first) // if name is smae or bigger than end
				{
					sec = end->second;
				}
				else
					sec = bpNode->getIndexMap()->begin()->second;
				return Find_Root(sec, name);
			}
			else // else go MLC
			{
				return Find_Root(bpNode->getMostLeftChild(), name);
			}
		}
	}
	bool dup(VaccinationData *); // check data is duplicated

	void delete_all(BpTreeNode *); // delete all data
};

#endif
