#pragma once

#include <string>
#include <iostream>
class ImageNode
{
	friend class TreeNode;
	friend class BinarySearchTree;
	friend class TreeManager;

private:
public:
	std::string m_name;
	std::string dirname;
	int unique_number;

	ImageNode() : m_name(m_name), dirname(dirname), unique_number(unique_number) {}
	ImageNode(std::string name, std::string dir, int number)
		: m_name(name),
		  dirname(dir),
		  unique_number(number)
	{
	}

	friend std::ostream &operator<<(std::ostream &os, const ImageNode &node)
	{
		os << "(node.m_name: " << node.m_name << "), "; // Debug with print
		return os;
	}
};
