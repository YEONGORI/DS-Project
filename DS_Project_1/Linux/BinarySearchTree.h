#pragma once

#include <iostream>
#include <string>

#include "TreeNode.h"
#include "Manager.h"

Database_BST_Node *visit_inputdata(Database_BST_Node *t, ofstream *fout, int index);
Database_BST_Node *traversal_preorder(Database_BST_Node *t, ofstream *fout, int index);
Database_BST_Node *visit_inputdata(Database_BST_Node *t, ofstream *fout, int index);
void traversal_inorder(Database_BST_Node *t, ofstream *fout);


class Database_BST
{
public:
	Database_BST_Node *tree_root;

	Database_BST()
	{
		tree_root = NULL;	
	};

	~Database_BST()
	{
		// delete[] tree_root;
	};

	void insert(Loaded_LIST_Node *node)
	{
		int idx = stoi(node->index);
		Database_BST_Node *p = tree_root, *pp = NULL;

		while (p)
		{
			pp = p;
			if (idx < p->tree_data->index)
				p = p->tree_left;
			else if (idx > p->tree_data->index)
				p = p->tree_right;
		}

		ImageNode *img_node = new ImageNode(node->file_name, node->dir_name, idx);
		p = new Database_BST_Node(img_node, NULL, NULL);
	
		if (tree_root != NULL)
		{
			if (idx < pp->tree_data->index)
				pp->tree_left = p;
			else
				pp->tree_right = p;
		}
		else
			tree_root = p;
	};

	void deletion(int index)
	{
		Database_BST_Node *p = tree_root;
		Database_BST_Node *pp = NULL;
		while (p && index != p->tree_data->index)
		{
			pp = p;
			if (index < p->tree_data->index)
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
			Database_BST_Node *pp = p;
			Database_BST_Node *prev = p->tree_left;
			Database_BST_Node *curr = p->tree_left->tree_right;

			while (curr)
			{
				pp = prev;
				prev = curr;
				curr = curr->tree_right;
			}

			p->tree_data->index = prev->tree_data->index;
			if (pp == p)
				pp->tree_left = prev->tree_left;
			else
				pp->tree_right = prev->tree_left;
			delete prev;
		}
	};
};