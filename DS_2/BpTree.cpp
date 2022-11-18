#include "BpTree.h"
#include "BpTreeNode.h"
#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include <map>
#include <typeindex>

bool BpTree::Insert(int key, set<string> set)
{
	FrequentPatternNode *fpn = new FrequentPatternNode;
	int s = set.size();
	fpn->setFrequency(s);
	fpn->InsertList(set);
	if (root == nullptr)
	{
		BpTreeDataNode *newdatanode = new BpTreeDataNode();
		newdatanode->insertDataMap(key, fpn);
		root = newdatanode;
		return true;
	}
	// else
	// {
	// 	BpTreeNode *cur = root;
	// 	while (1)
	// 	{
	// 		if (root->getDataMap()->size() <= order)
	// 		{
	// 			cur->insertDataMap(key, fpn);
	// 			break;
	// 		}
	// 		else
	// 		{
	// 			multimap<int, BpTreeNode *>::iterator it2 = cur->getIndexMap()->begin();
	// 			if (key <= it2->first)
	// 			{
	// 				cur = cur->getMostLeftChild();
	// 				continue;
	// 			}
	// 			else
	// 			{
	// 				if (key > it2->first)
	// 				{
	// 					it2++;
	// 					cur = it2->second;
	// 					continue;
	// 				}
	// 				cur = it2->second;
	// 			}
	// 		}
	// 	}
	// }

	BpTreeNode *cur = root;
	if (root->getDataMap()->size() <= order)
	{
		root->insertDataMap(key, fpn);
		return true;
	}
	else
	{
		while (cur->getMostLeftChild())
			cur = cur->getMostLeftChild();

		while (cur->getNext() && cur->getDataMap()->end()->first < key)
		{
			cur = cur->getNext();
		}

		cur->insertDataMap(key, fpn);
	}
}

BpTreeNode *BpTree::searchDataNode(int n)
{
	BpTreeNode *cur = root;

	while (cur->getMostLeftChild())
		cur = cur->getMostLeftChild();
	// cur->insertDataMap(2147483647, NULL);
	if (cur->getDataMap() == NULL || cur->getDataMap()->begin()->first > n)
		return cur;

	while (cur->getNext())
	{
		for (auto it = cur->getDataMap()->begin(); it != cur->getDataMap()->end(); it++)
		{
			if (it->first <= n && n <= (++it)->first)
			{
				return cur;
			}
			--it;
		}
		cur = cur->getNext();
	}
	return cur;
}

void BpTree::splitDataNode(BpTreeNode *pDataNode)
{
	BpTreeDataNode *new_btd = new BpTreeDataNode;
	auto it = pDataNode->getDataMap()->begin();
	for (it; pDataNode->getDataMap()->size() / 2 + pDataNode->getDataMap()->begin; it++)
		;
	for (it; it != pDataNode->getDataMap()->end(); it++)
	{
		new_btd->insertDataMap(it->first, it->second);
	}

	it = new_btd->getDataMap()->begin();
	for (it; it != new_btd->getDataMap()->end(); it++)
	{
		pDataNode->deleteMap(it->first);
	}

	if (pDataNode->getNext() != NULL)
	{
		pDataNode->getNext()->setPrev(new_btd);
		new_btd->setNext(pDataNode->getNext());
	}
	pDataNode->setNext(new_btd);
	new_btd->setPrev(pDataNode);

	if (pDataNode->getParent() == NULL)
	{
		BpTreeIndexNode *new_idn = new BpTreeIndexNode;
		new_idn->insertIndexMap(new_btd->getDataMap()->begin()->first, new_btd);
		new_idn->setMostLeftChild(pDataNode);

		pDataNode->setParent(new_idn);
		new_btd->setParent(new_idn);
		root = new_idn;
	}
	else
	{
		pDataNode->getParent()->insertIndexMap(new_btd->getDataMap()->begin()->first, new_btd);
		new_btd->setParent(pDataNode->getParent());
		if (pDataNode->getParent()->getIndexMap()->size() == order)
		{
			splitIndexNode(pDataNode->getParent());
		}
	}
}

void BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
	// if no parent
	if (pIndexNode->getParent() == NULL)
	{
		auto it = pIndexNode->getIndexMap()->begin();
		BpTreeIndexNode *newindexnode = new BpTreeIndexNode;
		BpTreeIndexNode *newparentnode = new BpTreeIndexNode;
		root = newparentnode;

		for (it; pIndexNode->getIndexMap()->size() / 2; it++)
			;
		it++;
		newparentnode->insertIndexMap(it->first, it->second);
		it++;
		for (it; it != pIndexNode->getIndexMap()->end(); it++)
		{
			newindexnode->insertIndexMap(it->first, it->second);
		}

		newindexnode->setMostLeftChild(newparentnode->getIndexMap()->begin()->second);
		newparentnode->getIndexMap()->begin()->second = newindexnode;

		it = newindexnode->getIndexMap()->begin();
		for (it; it != newindexnode->getIndexMap()->end(); it++)
		{
			pIndexNode->deleteMap(it->first);
		}
		it = newparentnode->getIndexMap()->begin();
		pIndexNode->deleteMap(it->first);

		newparentnode->setMostLeftChild(pIndexNode);
		pIndexNode->setParent(newparentnode);
		newindexnode->setParent(newparentnode);
	}
	else
	{
		auto it = pIndexNode->getIndexMap()->begin();
		BpTreeIndexNode *newindexnode = new BpTreeIndexNode;
		BpTreeIndexNode *newparentnode = new BpTreeIndexNode;
		root = newparentnode;
		//부모 노드에 값 채움
		for (int i = 0; i < pIndexNode->getIndexMap()->size() / 2; i++)
		{
			it++;
		}
		newparentnode->insertIndexMap(it->first, it->second);
		//자식 노드에 값 채움
		it++;
		for (it; it != pIndexNode->getIndexMap()->end(); it++)
		{
			newindexnode->insertIndexMap(it->first, it->second);
		}

		newindexnode->setMostLeftChild(newparentnode->getIndexMap()->begin()->second);
		// newparentnode->getIndexMap()->begin()->second = newindexnode;

		it = newindexnode->getIndexMap()->begin();
		for (it; it != newindexnode->getIndexMap()->end(); it++)
		{
			pIndexNode->deleteMap(it->first);
		}
		it = newparentnode->getIndexMap()->begin();
		pIndexNode->deleteMap(it->first);

		// newindexnode->setParent(newparentnode);
		// pIndexNode->setParent(newparentnode);
		pIndexNode->pParent->insertIndexMap(newparentnode->getIndexMap()->begin()->first, newindexnode);

		// if parent is be fulled then split again
		if (pIndexNode->getParent()->getIndexMap()->size() == order)
		{
			splitIndexNode(pIndexNode->getParent());
		}
	}
}

bool BpTree::excessDataNode(BpTreeNode *pDataNode)
{
	cout << pDataNode->getDataMap()->size() << '\n';
	if (pDataNode->getDataMap()->size() > order - 1)
		return true; // order is equal to the number of elements
	else
		return false;
}

bool BpTree::excessIndexNode(BpTreeNode *pIndexNode)
{
	if (pIndexNode->getIndexMap()->size() > order - 1)
		return true; // order is equal to the number of elements
	else
		return false;
}

bool BpTree::printConfidence(string item, double item_frequency, double min_confidence)
{

	return true;
}
bool BpTree::printFrequency(string item, int min_frequency) // print winratio in ascending order
{

	return true;
}
bool BpTree::printRange(string item, int min, int max)
{

	return true;
}
void BpTree::printFrequentPatterns(set<string> pFrequentPattern, string item)
{
	*fout << "{";
	set<string> curPattern = pFrequentPattern;
	curPattern.erase(item);
	for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();)
	{
		string temp = *it++;
		if (temp != item)
			*fout << temp;
		if (it == curPattern.end())
		{
			*fout << "} ";
			break;
		}
		*fout << ", ";
	}
}
