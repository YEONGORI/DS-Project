#ifndef _BpTree_H_
#define _BpTree_H_

#include <map>
#include <fstream>
#include <iostream>

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"

class BpTree
{
public:
	BpTreeNode *root;
	ofstream *fout;

	int order; // m children
	int node_count;

	BpTree()
	{
		root = new BpTreeDataNode;
		order = 3;
		node_count = 0;
	}
	BpTree(ofstream *fout, int order = 3)
	{
		this->order = order;
		this->fout = fout;
	}
	~BpTree();
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
};

#endif
