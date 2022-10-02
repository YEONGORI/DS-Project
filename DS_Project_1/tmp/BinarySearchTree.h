#pragma once

#include "TreeNode.h"
#include "Manager.h"
#include <iostream>
#include <string>

class BinarySearchTree
{
	friend class TreeManager;
private:
	TreeNode * m_root;

public:
	BinarySearchTree() { m_root = NULL; }
	~BinarySearchTree();

	void insert(Node* node)
	{
		TreeNode* p = m_root, *pp = NULL;
		while(p) {
			pp = p;
			if (stoi(node->number) < p->m_data.unique_number) p = p->m_left;
			else if (stoi(node->number) > p->m_data.unique_number) p = p->m_right;
		}

		p = new TreeNode;
		p->m_data.dirname = node->dir;
		p->m_data.m_name = node->file;
		p->m_data.unique_number = stoi(node->number);
		if (m_root != NULL)
		{
			if (stoi(node->number) < pp->m_data.unique_number) pp ->m_left = p;
			else pp->m_right = p;
		}
		else
			m_root = p;
	}; //Data

	void deletion(  ); //unique number = key

	friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree) {

	// fill in your code to print a node in binary search tree
		return os;
	}
};
