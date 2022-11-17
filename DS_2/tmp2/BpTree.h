#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeNode.h"
#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "VaccinationData.h"
#include "AVLTree.h"



class BpTree{
private:
	BpTreeNode*	root;
	int			order;		// m children

public:
	BpTree(int order = 3){
		root = NULL;
		this->order = order;
	}

	bool		Insert(VaccinationData* newData, AVLTree* avl);
	bool		exceedDataNode(BpTreeNode* pDataNode);
	bool		exceedIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode*	searchDataNode(string n); //search VaccinationData node
	bool	SearchRange(string start, string end);
	bool	Print(); // print all 
	bool	EMPTY(){if(root==NULL) return true; else return false;};
	int 	IsLeftFirst(string left, string right);
	void 	deletebp();
};

#endif
