#include <iostream>

using namespace std;

template<class T>
class treenode;

template<class k, class e>
class dictionary {
public:
	virtual void ascend(void) const = 0;

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
	return &p->data;
}

template<class k, class e>
void bst<k, e>::insert(const pair<k, e>& thepair) {
	treenode<pair<k, e> > *p = root, *pp = NULL;

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
		else
			pp->rightchild = p;
	}
	else
		root = p;
}

template<class k, class e>
void bst<k, e>::Delete(k kk) {
	treenode<pair<k,e>> *p = root, *q = 0;
	while (p && k != p->data.first) {
		q = p;
		if (k < p->data.first)
			p = p->leftchild;
		else
			p = p->rightchild;
	}
	if (p == 0)
		return;

	if (p->leftchild == 0 && p->rightchild == 0) {
		if (q == 0)
			root = 0;
		else if (q->leftchild == p)
			q->leftchild = 0;
		else
			q->rightchild = 0;
		delete p;
	}
	if (p->leftchild == 0) {
		if (q == 0)
			root = p->rightchild;
		else if (q->leftchild == p)
			q->leftchild = p->rightchild;
		else
			q->rightchild = p->rightchild;
		delete p;
	}
	if (p->rightchild == 0) {
		if (q == 0)
			root = p->leftchild;
		else if (q->leftchild = p)
			q->leftchild = p->leftchild;
		else
			q->rightchild = p->leftchild;
		delete p;
	}

	treenode<pair<k, e>> *prevprev = p, *prev = p->rightchild, *curr = p->rightchild->leftchild;

	while (curr) {
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
