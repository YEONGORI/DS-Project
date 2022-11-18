#pragma once
#include "FrequentPatternNode.h"
#include "FPNode.h"
class BpTreeNode
{
public:
    BpTreeNode *pParent;
    BpTreeNode *pMostLeftChild;
    BpTreeNode()
    {
        pParent = nullptr;
        pMostLeftChild = nullptr;
    }
    ~BpTreeNode()
    {
    }

    void setMostLeftChild(BpTreeNode *pN) { pMostLeftChild = pN; }
    void setParent(BpTreeNode *pN) { pParent = pN; }

    BpTreeNode *getParent() { return pParent; }
    BpTreeNode *getMostLeftChild() { return pMostLeftChild; }

    virtual void setNext(BpTreeNode *pN) {}
    virtual void setPrev(BpTreeNode *pN) {}
    virtual BpTreeNode *getNext() { return NULL; }
    virtual BpTreeNode *getPrev() { return NULL; }

    virtual void insertDataMap(int n, FrequentPatternNode *pN) {}
    virtual void insertIndexMap(int n, BpTreeNode *pN) {}
    virtual void deleteMap(int n) {}

    virtual multimap<int, BpTreeNode *> *getIndexMap()
    {
        multimap<int, BpTreeNode *> m;
        return &m;
    }
    virtual multimap<int, FrequentPatternNode *> *getDataMap()
    {
        multimap<int, FrequentPatternNode *> m;
        return &m;
    }
};
