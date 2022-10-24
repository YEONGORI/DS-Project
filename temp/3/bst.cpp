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
    pair<K, E> *Get(TreeNode<pair<K, E>> *P, const K &k);
    void Insert(const pair<K, E> &thePair);
    void Delete(K k);
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
}

template <class K, class E>
void BST<k, e>::insert(const pair<k, e> &thepair)
{
    TreeNode<pair<K, E>> *p = root, *pp = NULL;
}