#include <iostream>

using namespace std;

template <class K, class E>
class AvlNode
{
    friend class AVL<K, E>;

public:
    AvlNode(const K &k, const E &e)
    {
        key = k;
        element = e;
        bf = 0;
        leftChild = rightChild = NULL;
    }

private:
    K key;
    E element;
    int bf;
    AvlNode<K, E> *leftChild, *rightChild;
};

template <class K, class E>
class AVL
{
public:
    AVL() : root(NULL){};
    void Insert(const K &, const E &);

private:
    AvlNode<K, E> *root;
};

template <class K, class E>
void AVL<K, E>::Insert(const K &k, const E &e)
{
    if (root == NULL)
    {
        root = new AvlNode<K, E>(K, E);
        return;
    }
    AvlNode<K, E> *a = root;
    AvlNode<K, E> *pa = NULL;
    AvlNode<K, E> *p = root;
    AvlNode<K, E> *pp = NULL;
    AvlNode<K, E> *rootSub = NULL;

    while (p != NULL)
    {
        if (p->bf != 0)
        {
            a = p;
            pa = pp;
        }

        if (k < p->key)
        {
            pp = p;
            p = p->leftChild;
        }
        else if (k > p->key)
        {
            pp = p;
            p = p->rightChild;
        }
        else
        {
            p->element = e;
            return;
        }
    }

    AvlNode<K, E> *y = new AvlNode<K, E>(k, e);
    if (k < pp->key)
        pp->leftChild = y;
    else
        pp->rightChild = y;
    int d;
    AvlNode<K, E> *b, *c;

    if (k > a->key)
    {
        b = p = a->rightChild;
        d = -1;
    }
    else
    {
        b = p = a->leftChild;
        d = 1;
    }

    while (p != y)
    {
        if (k > p->key)
        {
            p->bf = -1;
            p = p->rightChild;
        }
        else
        {
            p->bf = 1;
            p = p->leftChild;
        }
    }

    if (a->bf == 0 || a->bf + d == 0)
    {
        a->bf += d;
        return;
    }

    if (d == 1)
    {
        if (b->bf == 1)
        {
            a->leftChild = b->rightChild;
            b->rightChild = a;
            a->bf = 0;
            b->bf = 0;
            rootSub = b;
        }
        else
        {
            c = b->rightChild;
            b->rightChild = c->leftChild;
            a->leftChild = c->rightChild;
            c->leftChild = b;
            c->rightChild = a;
            switch (c->bf)
            {
            case 0:
                b->bf = 0;
                a->bf = 0;
                break;
            case 1:
                a->bf = -1;
                b->bf = 0;
                break;
            case -1:
                b->bf = 1;
                a->bf = 0;
            }
            c->bf = 0;
            rootSub = c;
        }
    }
}