#include "BpTree.h"
#include "BpTreeNode.h"
#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include <map>

bool BpTree::Insert(int key, set<string> set)
{
	FrequentPatternNode *fpn = new FrequentPatternNode;

	if (cnt < order)
	{
		if(cnt == 0){
			fpn->InsertList(set);
			root->insertDataMap(key, fpn);
		}
		else{
			fpn = root->getDataMap()->find(key)->second;
			fpn->InsertList(set);
			root->insertDataMap(key, fpn);
		}
		cnt++;
	}
	else
	{
		BpTreeNode *cur = root;
		while (cur->getMostLeftChild())
			cur = cur->getMostLeftChild();
		auto it = cur->getDataMap()->end();
		it--;
		while (cur->getNext() && it->first < key)
		{
			it = cur->getDataMap()->end();
			it--;
			cur = cur->getNext();
		}
		// insert
		if(cur->getDataMap()->find(key)==cur->getDataMap()->end()){
			fpn->InsertList(set);
			cur->insertDataMap(key, fpn);
		}
		else{
			fpn = cur->getDataMap()->find(key)->second;
			fpn->InsertList(set);
			cur->insertDataMap(key, fpn);
		}
	}

	return true;
}

BpTreeNode *BpTree::searchDataNode(int n)
{
	BpTreeNode *cur = root;

	while (cur->getMostLeftChild())
		cur = cur->getMostLeftChild();

	while (cur->getNext())
	{
		for (auto it = cur->getDataMap()->begin(); it != cur->getDataMap()->end(); it++)
		{
			if (it->first >= n)
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
	for (int i = 0; i < pDataNode->getDataMap()->size() / 2; i++)
	{
		it++;
	}

	for (it; it != pDataNode->getDataMap()->end(); it++)
	{
		new_btd->insertDataMap(it->first, it->second);
	}
	int data_size = pDataNode->getDataMap()->size();
	for (int i = 0; i <= data_size / 2; i++)
	{
		it = pDataNode->getDataMap()->end();
		it--;
		pDataNode->getDataMap()->erase(it);
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
		if (excessIndexNode(new_btd->getParent()))
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

		//�θ� ��忡 �� ä��
		for (int i = 0; i < pIndexNode->getIndexMap()->size() / 2; i++)
		{
			it++;
		}
		newparentnode->insertIndexMap(it->first, it->second);
		//�ڽ� ��忡 �� ä��
		it++;
		for (it; it != pIndexNode->getIndexMap()->end(); it++)
		{
			newindexnode->insertIndexMap(it->first, it->second);
		}

		newindexnode->setMostLeftChild(newparentnode->getIndexMap()->begin()->second);
		newparentnode->getIndexMap()->begin()->second = newindexnode;

		//���� ��� new��� �κ� ����
		int index_size = pIndexNode->getIndexMap()->size();
		for (int i = 0; i <= index_size / 2; i++)
		{
			it = pIndexNode->getIndexMap()->end();
			it--;
			pIndexNode->getIndexMap()->erase(it);
		}

		newparentnode->setMostLeftChild(pIndexNode);
		pIndexNode->setParent(newparentnode);
		newindexnode->setParent(newparentnode);
		root = newparentnode;
	}
	else
	{
		auto it = pIndexNode->getIndexMap()->begin();
		BpTreeIndexNode *newindexnode = new BpTreeIndexNode;
		BpTreeIndexNode *newparentnode = new BpTreeIndexNode;

		//�θ� ��忡 �� ä��
		for (int i = 0; i < pIndexNode->getIndexMap()->size() / 2; i++)
		{
			it++;
		}
		newparentnode->insertIndexMap(it->first, it->second);
		//�ڽ� ��忡 �� ä��
		it++;
		for (it; it != pIndexNode->getIndexMap()->end(); it++)
		{
			newindexnode->insertIndexMap(it->first, it->second);
		}

		newindexnode->setMostLeftChild(newparentnode->getIndexMap()->begin()->second);
		// newparentnode->getIndexMap()->begin()->second = newindexnode;

		//���� ��� new��� �κ� ����
		int index_size = pIndexNode->getIndexMap()->size();
		for (int i = 0; i <= index_size / 2; i++)
		{
			it = pIndexNode->getIndexMap()->end();
			it--;
			pIndexNode->getIndexMap()->erase(it);
		}

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
