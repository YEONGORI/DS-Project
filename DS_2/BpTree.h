#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include <fstream>
#include <iostream>

class BpTree
{
public:
	BpTreeNode *root;
	int order; // m children
	ofstream *fout;
	BpTree()
	{
		root = NULL;
		order = 3;
	}
	BpTree(ofstream *fout, int order = 3)
	{
		this->order = order;
		this->fout = fout;
	}
	~BpTree(){

	};

	/* essential */
	bool Insert(int key, set<string> set);
	bool excessDataNode(BpTreeNode *pDataNode);
	bool excessIndexNode(BpTreeNode *pIndexNode);
	void splitDataNode(BpTreeNode *pDataNode);
	void splitIndexNode(BpTreeNode *pIndexNode);
	BpTreeNode *getRoot() { return root; }
	BpTreeNode *searchDataNode(int n);

	void printFrequentPatterns(set<string> pFrequentPattern, string item);
	bool printFrequency(string item, int min_frequency);
	bool printConfidence(string item, double item_frequency, double min_confidence);
	bool printRange(string item, int min, int max);

	BpTreeNode *Find_Root(BpTreeNode *bpNode, int name) // find place that input the dat
	{
		if (!bpNode->getMostLeftChild())
		{
			return bpNode;
		}
		else
		{
			int target = bpNode->getIndexMap()->begin()->first;
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
};

#endif
