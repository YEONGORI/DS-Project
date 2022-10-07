#pragma once

#include "ImageNode.h"
#include <iostream>

class TreeNode
{
	friend class BinarySearchTree;
	friend class TreeManager;

public:
	ImageNode tree_data; // parameter must be added
	TreeNode *tree_left;
	TreeNode *tree_right;
	TreeNode() : tree_left(NULL), tree_right(NULL) {}
	~TreeNode() {}
	TreeNode(ImageNode &data, TreeNode *left = NULL, TreeNode *right = NULL)
	{
		this->tree_data = data;
		this->tree_left = left;
		this->tree_right = right;
	}

	TreeNode *getLeftNode() const { return tree_left; }
	TreeNode *getRightNode() const { return tree_right; }

	// friend std::ostream &operator<<(std::ostream &os, const TreeNode *node)
	// {
	// 	if (node != NULL)
	// 		os << node->tree_data;
	// 	return os;
	// }
};
