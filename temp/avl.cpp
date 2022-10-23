#include <iostream>

using namespace std;

template<class k, class e>
class AvlNode;

template<class k, class e>
class AVL {
public:
	AVL() : root(NULL) {};
	void insert(const k&, const e&);
	AvlNode *root;
};

template<class k, class e>
class AvlNode {
friend class AVL<k, e>;
public:
	AvlNode(const k& kk, const e& ee) {
		key = k;
		element = e;
		bf = 0;
		leftchild = rightchild = NULL;
	}
private:
	k key;
	e element;
	int bf;
	AvlNode<k, e> *leftchild, *rightchild;
};

template<class k, class e>
void AVL<k, e>::insert(const k& kk, const e& ee) {
	if (root == NULL) {
		root = new AvlNode<k, e>(k, e);
		return;
	}

	AvlNode<k, e> *a = root, *pa = NULL;
	AvlNode<k, e> *p = root, *pp = NULL;
	AvlNode<k, e> *rootsub = NULL;

	while (p != NULL) {
		if (p->bf != 0) 
			a = p; pa = pp;

		if (kk < p->key)
			pp = p; p = p->leftchild;
		else if (kk > p->key)
			pp = p;	p = p->rightchild;
		else {
			p->element = ee;
			return ;
		}
	}

	AvlNode<k, e> *y = new AvlNode<k, e>(k, e);
	if (kk < pp->key)
		pp->leftchild = y;
	else
		pp->rightchild = y;

	int d;
	AvlNode<k, e> *b, *c;

	if (kk > a->key) {
		b = p = a->rightchild;
		d = -1;
	}
	else {
		b = p = a->leftchild;
		d = 1;
	}

	while (p != y) {
		if (kk > p->key) {
			p->bf = -1;
			p = p->rightchild;
		}
		else {
			p->bf = 1;
			p = p->leftchild;
		}
	}

	if (a->bf == 0 || a->bf + d == 0) {
		a->bf += d;
		return;
	}

	if (d == 1) {
		if (b->bf == 1) {
			a->leftchild = b->rightchild;
			b->rightchild = a;
			a->bf = 0;
			b->bf = 0;
			rootsub = b;
		}
		else {
			c = b->rightchild;
			b->rightchild = c->leftchild;
			a->leftchild = c->rightchild;
			c->leftchild = b;
			c->rightchild = a;
			switch (c->bf)
			{
			case 0:
				b->bf = 0;
				a->bf = 0;
				break;
			case 1:
				a->bf = -1;
				b->bf = 0;
			case -1:
				b->bf = 1;
				a->bf = 0;
				break;
			}
			b->bf = 0;
			rootsub = c;
		}
	}
	else {
		if (b->bf == -1) {
			a->rightchild = b->leftchild;
			b->leftchild = a;
			a->bf = 0;
			b->bf = 0;
			rootsub = b;
		}
		else {
			c = b->leftchild;
			b->leftchild = c->rightchild;
			a->rightchild = c->leftchild;
			c->rightchild = b;
			c->leftchild = a;
			switch (c->bf)
			{
			case 0:
				b->bf = 0;
				a->bf = 0;
				break;
			case 1:
				b->bf = -1;
				a->bf = 0;
				break;
			case -1:
				a->bf = 1;
				b->bf = 0;
			default:
				break;
			}
			c->bf = 0;
			rootsub = c;
		}
	}
	if (pa == NULL)
		root = rootsub;
	else if (a == pa->leftchild)
		pa->leftchild = rootsub;
	else
		pa->rightchild = rootsub;
	return ;
}