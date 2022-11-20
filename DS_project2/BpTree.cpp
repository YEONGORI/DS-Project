#include "BpTree.h"
#include "BpTreeNode.h"
#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"

bool BpTree::Insert(int key, set<string> set)
{
	FrequentPatternNode *cur_fpn = new FrequentPatternNode;

	if (node_count < order) // Check root is data node
	{
		if (node_count == 0) // Check root is NULL
		{
			cur_fpn->InsertList(set);
			root->insertDataMap(key, cur_fpn);
		}
		else
		{
			cur_fpn = root->getDataMap()->find(key)->second;
			cur_fpn->InsertList(set);
			root->insertDataMap(key, cur_fpn);
		}
		node_count++;
	}
	else // root is index node
	{
		BpTreeNode *cur_btn = root;
		while (cur_btn->getMostLeftChild()) // Find Data Node
			cur_btn = cur_btn->getMostLeftChild();

		auto item = cur_btn->getDataMap()->end();
		item--;

		while (cur_btn->getNext() && item->first < key) // Find Insert Position
		{
			item = cur_btn->getDataMap()->end();
			item--;
			cur_btn = cur_btn->getNext();
		}

		if (cur_btn->getDataMap()->find(key) == cur_btn->getDataMap()->end()) // Check Position is Tree's end
		{
			cur_fpn->InsertList(set);
			cur_btn->insertDataMap(key, cur_fpn);
		}
		else
		{
			cur_fpn = cur_btn->getDataMap()->find(key)->second;
			cur_fpn->InsertList(set);
			cur_btn->insertDataMap(key, cur_fpn);
		}
	}
	return true;
}

BpTreeNode *BpTree::searchDataNode(int n)
{
	BpTreeNode *cur_btn = root;

	while (cur_btn->getMostLeftChild()) // Find Data Node
		cur_btn = cur_btn->getMostLeftChild();

	while (cur_btn->getNext()) // Travelling all data nodes
	{
		for (auto item = cur_btn->getDataMap()->begin(); item != cur_btn->getDataMap()->end(); item++)
		{
			if (item->first >= n) // Return node that meets the condition for the first time
				return cur_btn;
			item--;
		}
		cur_btn = cur_btn->getNext();
	}
	return cur_btn;
}

void BpTree::splitDataNode(BpTreeNode *pDataNode)
{
	int item_cnt;

	BpTreeDataNode *new_dtn = new BpTreeDataNode;
	auto item = pDataNode->getDataMap()->begin();
	for (int i = 0; i < pDataNode->getDataMap()->size() / 2; i++) // Find dtn's middle position
		item++;

	for (item; item != pDataNode->getDataMap()->end(); item++) // Make New Data Node
		new_dtn->insertDataMap(item->first, item->second);

	item_cnt = pDataNode->getDataMap()->size();
	for (int i = 0; i <= item_cnt / 2; i++) // Erase Data that used to make data node
	{
		item = pDataNode->getDataMap()->end();
		item--;
		pDataNode->getDataMap()->erase(item);
	}

	if (pDataNode->getNext() != NULL) // Set Prev & Next
	{
		pDataNode->getNext()->setPrev(new_dtn);
		new_dtn->setNext(pDataNode->getNext());
	}

	pDataNode->setNext(new_dtn);
	new_dtn->setPrev(pDataNode);
	if (pDataNode->getParent() == NULL) // Parent Node doesn't exist
	{
		BpTreeIndexNode *new_idn = new BpTreeIndexNode;
		new_idn->insertIndexMap(new_dtn->getDataMap()->begin()->first, new_dtn);
		new_idn->setMostLeftChild(pDataNode);

		pDataNode->setParent(new_idn);
		new_dtn->setParent(new_idn);
		root = new_idn;
	}
	else
	{
		pDataNode->getParent()->insertIndexMap(new_dtn->getDataMap()->begin()->first, new_dtn);
		new_dtn->setParent(pDataNode->getParent());
		if (excessIndexNode(new_dtn->getParent()))
			splitIndexNode(pDataNode->getParent());
	}
	new_dtn = NULL;
	delete new_dtn;
}

void BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
	int item_cnt;
	BpTreeIndexNode *new_idn = new BpTreeIndexNode;
	BpTreeIndexNode *new_par_idn = new BpTreeIndexNode;
	auto item = pIndexNode->getIndexMap()->begin();
	for (int i = 0; i < pIndexNode->getIndexMap()->size() / 2; i++) // Find dtn's middle position
		item++;
	new_par_idn->insertIndexMap(item->first, item->second);
	item++;
	for (item; item != pIndexNode->getIndexMap()->end(); item++) // Make New index node
		new_idn->insertIndexMap(item->first, item->second);
	if (pIndexNode->getParent() == NULL) // Parent Node doesn't exist
	{
		new_idn->setMostLeftChild(new_par_idn->getIndexMap()->begin()->second);
		new_par_idn->getIndexMap()->begin()->second = new_idn;
		item_cnt = pIndexNode->getIndexMap()->size();

		for (int i = 0; i <= item_cnt / 2; i++) // // Erase Data that used to make index node
		{
			item = pIndexNode->getIndexMap()->end();
			item--;
			pIndexNode->getIndexMap()->erase(item);
		}

		new_par_idn->setMostLeftChild(pIndexNode);
		pIndexNode->setParent(new_par_idn);
		new_idn->setParent(new_par_idn);
		root = new_par_idn;
	}
	else
	{
		new_idn->setMostLeftChild(new_par_idn->getIndexMap()->begin()->second);
		item_cnt = pIndexNode->getIndexMap()->size();

		for (int i = 0; i <= item_cnt / 2; i++)
		{
			item = pIndexNode->getIndexMap()->end();
			item--;
			pIndexNode->getIndexMap()->erase(item);
		}

		pIndexNode->pParent->insertIndexMap(new_par_idn->getIndexMap()->begin()->first, new_idn);
		if (pIndexNode->getParent()->getIndexMap()->size() == order) // Check if the newly added parent node exceeded the order
			splitIndexNode(pIndexNode->getParent());
	}
	new_idn = NULL;
	new_par_idn = NULL;
	delete new_idn;
	delete new_par_idn;
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
	return;
}
