#include <iostream>

using namespace std;

template <class A>
class TreeNode;

template <class K, class E>
class BST
{
public:
	virtual void ascend(void) const = 0;

	pair<K, E> *Get(const K &k);
	pair<K, E> *Get(TreeNode<pair<K, E>> *p, const K &k);
	void Insert(const pair<K, E> &thePair);
	void Delete(K k)
};

template <class K, class E>
pair<K, E> *BST<K, E>::Get(const K &k)
{
	return Get(root, k);
};

template <class K, class E>
pair<K, E> *BST<K, E>::Get(TreeNode<pair<K, E>> *p, const K &k)
{
	if (p == NULL)
		return NULL;
	if (k < p->data.first)
		return Get(p->leftChild, k);
	if (k > p->data.first)
		return Get(p->rightChild, k);
	return &p->data;
};

template <class k, class e>
void BST<k, e>::insert(const pair<k, e> &thepair)
{
	treenode<pair<k, e>> *p = root, *pp = NULL;

	template <class K, class E>
	void BST<K, E>::Insert(const pair<K, E> &thePair)
	{
		TreeNode<pair<K, E>> *p = root;
		TreeNode<pair<K, E>> *pp = NULL;
		while (p)
		{
			pp = p;
			if (thePair.first < p->data.first)
				p = p->leftChild;
			else if (thePair.first > p->data.first)
				p = p->rightChild;
			else
			{
				p->data.second = thePair.second;
				return;
			}
		}

		p = new TreeNode<pair<K, E>>(thePair);
		if (root != NULL)
		{
			if (thePair.first < pp->data.first)
				pp->leftChild = p;
			else
				pp->rightchild = p;
		}
		else
			root = p;
	}

	template <class K, class E>
	void BST<K, E>::Delete(K k)
	{
		TreeNode<pair<K, E>> *p = root;
		TreeNode<pair<K, E>> *q = 0;
		while (p && (k != p->data.first))
		{
			q = p;
			if (k < p->data.first)
				p = p->leftchild;
			else
				p = p->rightchild;
		}
		if (p == 0)
			return;
		if (p->LeftChild == 0 && p->RightChild == 0)
		{
			if (q == 0)
				root = 0;
			else if (q->leftchild == p)
				q->leftchild = 0;
			else
				q->rightchild = 0;
			delete p;
		}

		if (p->LeftChild == 0)
		{
			if (q == 0)
				root = p->rightchild;
			else if (q->leftchild == p)
				q->leftchild = p->rightchild;
			else
				q->rightchild = p->rightchild;
			delete p;
		}

		if (p->RightChild == 0)
		{
			if (q == 0)
				root = p->leftchild;
			else if (q->leftchild = p)
				q->leftchild = p->leftchild;
			else
				q->rightchild = p->leftchild;
			delete p;
		}

		treenode<pair<k, e>> *prevprev = p, *prev = p->rightchild, *curr = p->rightchild->leftchild;

		while (curr)
		{
			prevprev = prev;
			prev = curr;
			curr = curr->leftchild;
		}

		p->data = prev->data;
		if (prevprev == p)
			prevprev->rightchild = prev->rightchild;
		else
			prevprev->leftchild = prev->rightchild;
		delete prev;
	}

	int main(void)
	{

		return 0;
	}
