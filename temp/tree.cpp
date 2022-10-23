#include <iostream>

using namespace std;

template<class T>
class TreeNode {
	T data;
	TreeNode<T> *leftChild, *rightChild;

	TreeNode() {
		leftChild = rightChild = NULL;
	};
};