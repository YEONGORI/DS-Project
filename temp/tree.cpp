#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class TreeNode
{
public:
	T data;
	TreeNode<t> *leftChild, *rightChild;
	TreeNode()
	{
		leftChild = rightChild = NULL;
	}

	void PreOrder(TreeNode<T> *t);
	void InOrder(TreeNode<t> *t);
	void PostOrder(TreeNode<T> *t);
	void LevelOrder(TreeNode<T> *t);
};

template <class T>
void PreOrder(TreeNode<T> *t)
{
	if (t != NULL)
	{
		Visit(t);
		PreOrder(t->leftChild);
		PreOrder(t->rightChild);
	}
}

template <class T>
void InOrder(TreeNode<T> *t)
{
	if (t != NULL)
	{
		InOrder(t->leftChild);
		Visit(t);
		InOrder(t->rightChild);
	}
}

template <class T>
void PostOrder(TreeNode<T> *t)
{
	if (t != NULL)
	{
		PostOrder(t->leftChild);
		PostOrder(t->rightChild);
		Visit(t);
	}
};

template <class T>
void LevelOrder(TreeNode<T> *t)
{
	Queue<TreeNode<T> *> q;
	TreeNode<T> *currentNode = root;
	while (currentNode)
	{
		Visit(currentNode);
		if (currentNode->leftChild)
			q.push(currentNode->leftChild);
		if (currentNode->rightChild)
			q.push(currentNode->rightChild);
		if (q.IsEmpty())
			return;
		currentNode = q.Front();
		q.Pop();
	}
}

int main(void)
{

	return 0;
}