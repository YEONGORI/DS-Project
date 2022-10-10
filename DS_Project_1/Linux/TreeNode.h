#pragma once

#include "ImageNode.h"
#include <iostream>

class TreeNode
{
public:
	ImageNode *tree_data; // parameter must be added
	TreeNode *tree_left;
	TreeNode *tree_right;

	TreeNode() {};

	TreeNode(ImageNode *data, TreeNode *left, TreeNode *right) :
	tree_data(data), tree_left(left), tree_right(right) {};

	~TreeNode() {}

	TreeNode *getLeftNode() const { return tree_left; }
	TreeNode *getRightNode() const { return tree_right; }
};