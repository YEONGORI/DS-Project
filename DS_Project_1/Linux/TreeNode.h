#pragma once

#include "ImageNode.h"
#include <iostream>

class Database_BST_Node
{
public:
	ImageNode *tree_data; // parameter must be added
	Database_BST_Node *tree_left;
	Database_BST_Node *tree_right;

	Database_BST_Node() {};

	Database_BST_Node(ImageNode *data, Database_BST_Node *left, Database_BST_Node *right) :
	tree_data(data), tree_left(left), tree_right(right) {};

	~Database_BST_Node() {}

	Database_BST_Node *getLeftNode() const { return tree_left; }
	Database_BST_Node *getRightNode() const { return tree_right; }
};