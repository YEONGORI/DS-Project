#pragma once

#include <cstring>
#include <map>
#include <cmath>
using namespace std;
class FPNode
{

public:
	int frequency;
	FPNode* parent;
	FPNode* next;
	// FPNode* children;
	map<string, FPNode*> children;
	FPNode(){
		frequency = 1;
		parent = NULL;
		next = NULL;
	}
	~FPNode();
	void setParent(FPNode* node) { this->parent = node; }
	void setNext(FPNode* node) { next = node; }
	void pushchildren(string item, FPNode* node) { children.insert(map<string, FPNode*>::value_type(item, node)); }
	void updateFrequency(int frequency) { this->frequency += frequency; }

	int getFrequency() { return frequency; }
	FPNode* getParent() { return parent; }
	FPNode* getNext() { return next; }
	FPNode* getChildrenNode(string item);
	map<string, FPNode*> getChildren() { return children; }
};


