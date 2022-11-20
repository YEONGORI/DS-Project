#include "FPNode.h"

FPNode::FPNode() // constructor
{
	fp_count = 0;
	frequency = 0;

	parent = NULL;
	next = NULL;
}

FPNode::~FPNode() // destructor
{
}

FPNode *FPNode::getChildrenNode(string item)
{
	map<string, FPNode *>::iterator it = children.find(item);
	if (it == children.end())
		return NULL;
	FPNode *findNode = it->second;
	return findNode;
}
