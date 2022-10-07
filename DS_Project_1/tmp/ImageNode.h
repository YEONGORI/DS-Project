#pragma once

#include <string>
#include <iostream>

using namespace std;

class ImageNode
{
	friend class TreeNode;
	friend class BinarySearchTree;
	friend class TreeManager;

private:
public:
	string f_name;
	string d_name;
	int index;

	ImageNode() :
	f_name(f_name), d_name(d_name), index(index) {};

	ImageNode(string name, string dir, int index) :
		f_name(name), d_name(dir), index(index) {};

	// friend ostream &operator<<(ostream &os, const ImageNode &node)
	// {
	// 	os << "(node.f_name: " << node.f_name << "), "; // Debug with print
	// 	return os;
	// }
};
