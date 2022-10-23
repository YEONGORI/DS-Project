#include <iostream>
#include <algorithm>
using namespace std;

template<class K, class E>
class BST {
public:
	pair<K, E> *root;
	pair<K, E> *leftChild;
	pair<K, E> *rightChild;

	pair<K, E>* Get(const K& k);
	pair<K, E>* Get(TreeNode<pair<K, E> > *p, const K& k);
	void Insert(const pair<K, E>& thePair);

};

template<class K, class E>
pair<K, E>* BST<K, E>::Get(const K& k) {
	return Get(root, k);
};

template<class K, class E>
pair<K, E>* BST<K, E>::Get(TreeNode<pair<K, E> > *p, const K& k) {
	if (p == NULL) return NULL;
	if (k < p->data.first) return Get(p->leftChild, k);
	if (k > p->data.first) return Get(p->rightChild, k);
	return &p->data;
};

template<class K, class E>
void BST<K, E>::Insert(const pair<K, E>& thePair) {
	TreeNode<pair<K, E>> *p = root;
	TreeNode<pair<K, E>> *pp = NULL;
	while (p) {
		pp = p;
		if (thePair.first < p->data.first)
			p = p->leftChild;
		else if (thePair.first > p->data.first)
			p = p->rightChild;
		else {
			p->data.second = thePair.second;
			return ;
		}
	}

	p = new TreeNode<pair<K, E>> (thePair);
	if (root != NULL) {
		if (thePair.first < pp->data.first)
			pp->leftChild = p;
		else
			pp->rightChild = p;
	}
	else
		root = p;
};

template<class K, class E>
void BST<K, E>::Delete(K k) {
	TreeNode<pair<K, E>> *p = root;
	TreeNode<pair<K, E>> *q = 0;
	while (p && (k != p->data.first)) {
		q = p;
		if (k < p->data.first)
			p = p->LeftChild;
		else
			p = p->RightChild;
	}
	if (p == 0)
		return ;
	if (p->LeftChild == 0 && p->RightChild == 0) {
		if (q == 0)
			root = 0;
		else if (q->LeftChild == p)
			q->LeftChild = 0;
		else
			q->RightChild = 0;
		delete p;
	}

	if (p->LeftChild == 0) {
		if (q == 0)
			root = p->RightChild;
		else if (q->LeftChild == p)
			q->LeftChiuld = p->RightChild;
		else
			q->RightChild = p->RightChild;
		delete p;
	}

	if (p->RightChild == 0) {
		if (q == 0)
			root = p->LeftChild;
		else if (q->LeftChild == 0)
			q->LeftChild = p->LeftChild;
		else
			q->RightChild = p->LeftChild;
		delete p;
	}

	TreeNode<pair<K, E>> *prevprev = p;
	TreeNode<pair<K, E>> *prev = p->RightChild;
	TreeNode<pair<K, E>> *curr = p->RightChild->LeftChild;

	while (curr) {
		prevprev = prev;
		prev = curr;
		curr = curr->LeftChild;
	}

	p->data = prev->data;
	if (prevprev == p)
		prevprev->RightChild = prev->RightChild;
	else
		prevprev->LeftChild = prev->RightChild;
	delete prev;
}

int main(void)
{
	
	return 0;
}