#pragma once

#include <iostream>
#include <string>

#include "TreeNode.h"
#include "Manager.h"
#include "BinarySearchTree.h"

#ifndef BINARY_SEARCH_TREE_H
# define BINARY_SEARCH_TREE_H


TreeNode *visit_inputdata(TreeNode *t, ofstream *fout, int index);
TreeNode *traversal_preorder(TreeNode *t, ofstream *fout, int index);
TreeNode *visit_inputdata(TreeNode *t, ofstream *fout, int index);
void traversal_inorder(TreeNode *t, ofstream *fout);

#endif

class BinarySearchTree
{
	friend class TreeManager;

public:
	int bst_size;
	TreeNode *tree_root;

	BinarySearchTree() {
		bst_size = 0;
		tree_root = NULL;
	};

	~BinarySearchTree();

	void insert(Node *node)
	{
		int idx = stoi(node->index);
		TreeNode *p = tree_root, *pp = NULL;

		while (p)
		{
			pp = p;
			if (idx < p->tree_data.index)
				p = p->tree_left;
			else if (idx > p->tree_data.index)
				p = p->tree_right;
			else
				;
		}

		p = new TreeNode;
		p->tree_data.d_name = node->dir_name;
		p->tree_data.f_name = node->file_name;
		p->tree_data.index = idx;
		if (tree_root != NULL)
		{
			if (idx < pp->tree_data.index)
				pp->tree_left = p;
			else
				pp->tree_right = p;
		}
		else
			tree_root = p;
		bst_size++;
	};

	void deletion(int index)
	{
		bst_size--;
		TreeNode *p = tree_root;
		TreeNode *pp = NULL;
		while (p && index != p->tree_data.index)
		{
			pp = p;
			if (index < p->tree_data.index)
				p = p->tree_left;
			else
				p = p->tree_right;
		}
		if (p == NULL)
			return;
		if (p->tree_left == NULL && p->tree_right == NULL)
		{
			if (pp == NULL)
				tree_root = NULL;
			else if (pp->tree_left == p)
				pp->tree_left = NULL;
			else
				pp->tree_right = NULL;
			delete p;
		}
		else if (p->tree_left == NULL)
		{
			if (pp == NULL)
				tree_root = p->tree_right;
			else if (pp->tree_left == p)
				pp->tree_left = p->tree_right;
			else
				pp->tree_right = p->tree_right;
			delete p;
		}
		else if (p->tree_right == 0)
		{
			if (pp == 0)
				tree_root = p->tree_left;
			else if (pp->tree_left == p)
				pp->tree_left = p->tree_left;
			else
				pp->tree_left = p->tree_left;
			delete p;
		}
		else
		{
			TreeNode *pp = p;
			TreeNode *prev = p->tree_left;
			TreeNode *curr = p->tree_left->tree_right;

			while (curr)
			{
				pp = prev;
				prev = curr;
				curr = curr->tree_right;
			}

			p->tree_data.index = prev->tree_data.index;
			if (pp == p)
				pp->tree_left = prev->tree_left;
			else
				pp->tree_right = prev->tree_left;
			delete prev;
		}
	};
};