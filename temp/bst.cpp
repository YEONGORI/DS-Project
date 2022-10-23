#include <iostream>

using namespace std;

<<<<<<< HEAD
template<class T>
class treenode;

template<class k, class e>
class dictionary {
=======
template <class A>
class TreeNode;

template <class K, class E>
class BST
{
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
public:
	virtual void ascend(void) const = 0;

<<<<<<< HEAD
	virtual pair<k e> *get(const K&) const = 0;

	virtual void insert(const pair<k, e>&) = 0;

	virtual void Delete(const k&) = 0;
};

template<class k, class e>
class bst {
public:
	treenode *root;

	pair<k, e>* get(const k& kk);
	pair<k, e>* get(treenode<pair<k, e> > *p, const k& kk);
	void insert(const pair<k, e>& thepair);
	void Delete(k kk);
};

template<class k, class e>
pair<k, e>* bst<k, e>::get(const k& kk) {
	return get(root, k);
}

template<class k, class e>
pair<k, e>* bst<k, e>::get(treenode<pair<k, e> > *p, const k& kk) {
	if (p == NULL) return NULL;
	if (k < p->data.first) return get(p->leftchild, k);
	if (k > p->data.first) return get(p->rightChild, k);
=======
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
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
	return &p->data;
}

template<class k, class e>
void bst<k, e>::insert(const pair<k, e>& thepair) {
	treenode<pair<k, e> > *p = root, *pp = NULL;

<<<<<<< HEAD
	while (p) {
		pp = p;
		if (thepair.first < p->data.first)
			p = p->leftchild;
		else if (thepair.first > p->data.first)
			p = p->rightchild;
		else {
			p->data.second = thepair.second;
			return ;
		}
	}

	p = new treenode<pair<k, e>> (thepair);
	if (root != NULL) {
		if (thepair.first < pp->data.first)
			pp->leftchild = p;
=======
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
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
		else
			pp->rightchild = p;
	}
	else
		root = p;
}

<<<<<<< HEAD
template<class k, class e>
void bst<k, e>::Delete(k kk) {
	treenode<pair<k,e>> *p = root, *q = 0;
	while (p && k != p->data.first) {
=======
template <class K, class E>
void BST<K, E>::Delete(K k)
{
	TreeNode<pair<K, E>> *p = root;
	TreeNode<pair<K, E>> *q = 0;
	while (p && (k != p->data.first))
	{
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
		q = p;
		if (k < p->data.first)
			p = p->leftchild;
		else
			p = p->rightchild;
	}
	if (p == 0)
		return;
<<<<<<< HEAD

	if (p->leftchild == 0 && p->rightchild == 0) {
=======
	if (p->LeftChild == 0 && p->RightChild == 0)
	{
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
		if (q == 0)
			root = 0;
		else if (q->leftchild == p)
			q->leftchild = 0;
		else
			q->rightchild = 0;
		delete p;
	}
<<<<<<< HEAD
	if (p->leftchild == 0) {
=======

	if (p->LeftChild == 0)
	{
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
		if (q == 0)
			root = p->rightchild;
		else if (q->leftchild == p)
			q->leftchild = p->rightchild;
		else
			q->rightchild = p->rightchild;
		delete p;
	}
<<<<<<< HEAD
	if (p->rightchild == 0) {
=======

	if (p->RightChild == 0)
	{
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
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

<<<<<<< HEAD



/*







*/

template<class T>
class treenode {
	T data;
	treenode<T> *leftchild, *rightchild;

	treenode() {
		leftchild = rightchild = NULL;
	}
};
=======
int main(void)
{

	return 0;
}
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
