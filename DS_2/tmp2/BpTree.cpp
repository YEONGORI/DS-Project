#include "BpTree.h"
#include "string"

bool BpTree::Insert(VaccinationData *newData, AVLTree *avl)
{
	BpTreeNode *cur;
	if (newData->GetVaccineName() == "Janssen")
	{
		if (newData->GetTimes() >= 1)
		{
			// send to AVL
			avl->Insert(newData);
		}
	}
	else // other vaccines
	{
		if (newData->GetTimes() >= 2)
		{
			// send to AVL
			avl->Insert(newData);
		}
	}
	if (root == NULL)
	{
		BpTreeDataNode *newdatanode = new BpTreeDataNode();
		newdatanode->insertDataMap(newData->GetUserName(), newData);
		root = newdatanode;
	}
	else
	{
		map<string, BpTreeNode *>::iterator i;
		cur = root;
		while (1)
		{
			// if leafnode break;
			if (cur->isdatanode() == true)
			{
				map<string, VaccinationData *>::iterator j;
				j = cur->getDataMap()->begin();
				for (j; j != cur->getDataMap()->end(); j++)
				{
					if (IsLeftFirst(newData->GetUserName(), j->first) == -1) // if same person
					{
						j->second->SetTimesInc();
						if (j->second->GetVaccineName() == "Janssen")
						{
							if (j->second->GetTimes() >= 1)
							{
								// send to AVL
								avl->Insert(j->second);
							}
						}
						else // other vaccines
						{
							if (j->second->GetTimes() >= 2)
							{
								// send to AVL
								avl->Insert(j->second);
							}
						}
						break;
					}
				}
				cur->insertDataMap(newData->GetUserName(), newData);
				if (cur->getDataMap()->size() == 3)
				{
					splitDataNode(cur); // split
				}
				break;
			}
			// map's first
			i = cur->getIndexMap()->begin();
			if (IsLeftFirst(newData->GetUserName(), i->first) == 1) // if have to go leftside
			{
				cur = cur->getMostLeftChild();
				continue;
			}
			else
			{
				if (cur->getIndexMap()->size() == 1) // only one map
				{
					cur = i->second;
				}
				else // if map size is two
				{
					i++; // map's second
					if (IsLeftFirst(newData->GetUserName(), i->first) == 1)
					{
						i--;
						cur = i->second;
					}
					else
					{
						cur = i->second;
					}
				}
			}
		}
	}
}
BpTreeNode *BpTree::searchDataNode(string n)
{
	ofstream flog2; // log.txt
	flog2.open("log.txt", ios::app);
	if (root == NULL)
	{
		flog2 << "========== "
			  << "ERROR"
			  << " ==========" << endl;
		flog2 << "400" << endl;
		flog2 << "===========================" << endl
			  << endl;

		return NULL;
	}
	BpTreeNode *cur;
	map<string, VaccinationData *>::iterator i;
	cur = root;
	while (cur->getMostLeftChild() != NULL)
	{
		cur = cur->getMostLeftChild();
	}
	while (cur != NULL)
	{
		for (i = cur->getDataMap()->begin(); i != cur->getDataMap()->end(); i++)
		{
			if (i->first == n)
			{

				flog2 << "========== "
					  << "SEARCH_BP"
					  << " ==========" << endl;
				i->second->printinfo();
				flog2 << "=========================" << endl
					  << endl;
				return cur;
			}
		}
		cur = cur->getNext();
	}
	// no data
	flog2 << "========== "
		  << "ERROR"
		  << " ==========" << endl;
	flog2 << "400" << endl;
	flog2 << "===========================" << endl
		  << endl;
	flog2.close();
}

void BpTree::splitDataNode(BpTreeNode *pDataNode)
{
	map<string, VaccinationData *>::iterator i;
	BpTreeDataNode *newdatanode = new BpTreeDataNode();

	// split    [0]  /  [1][2]
	i = pDataNode->getDataMap()->begin();
	i++; // start from second
	for (i; i != pDataNode->getDataMap()->end(); i++)
	{
		// move [1][2] to new treenode
		newdatanode->insertDataMap(i->first, i->second);
	}
	i = newdatanode->getDataMap()->begin();
	for (i; i != newdatanode->getDataMap()->end(); i++)
	{
		// delete [1][2]
		pDataNode->deleteMap(i->first);
	}

	if (pDataNode->getNext() != NULL)
	{
		pDataNode->getNext()->setPrev(newdatanode);
		newdatanode->setNext(pDataNode->getNext());
	}
	pDataNode->setNext(newdatanode);
	newdatanode->setPrev(pDataNode);
	// if no parent
	if (pDataNode->getParent() == NULL)
	{
		// make parent
		BpTreeIndexNode *newindexnode = new BpTreeIndexNode();
		newindexnode->insertIndexMap(newdatanode->getDataMap()->begin()->first, newdatanode);
		newindexnode->setMostLeftChild(pDataNode);
		// link to parent
		pDataNode->setParent(newindexnode);
		newdatanode->setParent(newindexnode);
		root = newindexnode;
	}
	else // if have parent
	{
		pDataNode->getParent()->insertIndexMap(newdatanode->getDataMap()->begin()->first, newdatanode);
		newdatanode->setParent(pDataNode->getParent());
		if (pDataNode->getParent()->getIndexMap()->size() == 3)
		{
			splitIndexNode(pDataNode->getParent());
		}
	}
}

void BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
	map<string, BpTreeNode *>::iterator i;

	// if no parent
	if (pIndexNode->getParent() == NULL)
	{
		i = pIndexNode->getIndexMap()->begin();
		BpTreeIndexNode *newindexnode = new BpTreeIndexNode();
		BpTreeIndexNode *newparentnode = new BpTreeIndexNode();
		root = newparentnode;
		i++;
		// move [1] make new parent
		newparentnode->insertIndexMap(i->first, i->second);

		// move [2] to new node
		i++;
		newindexnode->insertIndexMap(i->first, i->second);
		newindexnode->setMostLeftChild(newparentnode->getIndexMap()->begin()->second);
		newparentnode->getIndexMap()->begin()->second = newindexnode;

		// delete [1][2] at original node
		i = newindexnode->getIndexMap()->begin();
		pIndexNode->deleteMap(i->first);
		i = newparentnode->getIndexMap()->begin();
		pIndexNode->deleteMap(i->first);

		newparentnode->setMostLeftChild(pIndexNode);
		pIndexNode->setParent(newparentnode);
		newindexnode->setParent(newparentnode);
	}
	else
	{
		i = pIndexNode->getIndexMap()->begin();
		BpTreeIndexNode *newindexnode = new BpTreeIndexNode();

		i++;
		// move [1] to parent
		newindexnode->setMostLeftChild(i->second);
		i->second = newindexnode;
		pIndexNode->insertIndexMap(i->first, i->second);

		// move [2] to new node
		i++;
		newindexnode->insertIndexMap(i->first, i->second);

		// delete [1][2] at original node
		i = newindexnode->getIndexMap()->begin();
		for (i; i != newindexnode->getIndexMap()->end(); i++)
		{
			pIndexNode->deleteMap(i->first);
		}
		newindexnode->setParent(pIndexNode->getParent());

		// if parent is be fulled then split again
		if (pIndexNode->getParent()->getIndexMap()->size() == 3)
		{
			splitIndexNode(pIndexNode->getParent());
		}
	}
}

bool BpTree::exceedDataNode(BpTreeNode *pDataNode)
{
}

bool BpTree::exceedIndexNode(BpTreeNode *pIndexNode)
{
}

bool BpTree::SearchRange(string start, string end)
{
	ofstream flog2; // log.txt
	flog2.open("log.txt", ios::app);
	if (root == NULL)
	{
		flog2 << "========== "
			  << "ERROR"
			  << " ==========" << endl;
		flog2 << "400" << endl;
		flog2 << "===========================" << endl
			  << endl;

		return false;
	}
	BpTreeNode *cur;
	map<string, VaccinationData *>::iterator i;

	cur = root;
	char i_1;
	char start_1;
	char end_1;
	int find = 0;
	end_1 = end[0];

	start_1 = start[0];

	while (cur->getMostLeftChild() != NULL)
	{
		cur = cur->getMostLeftChild();
	}

	while (cur != NULL)
	{
		for (i = cur->getDataMap()->begin(); i != cur->getDataMap()->end(); i++)
		{
			i_1 = i->first[0];

			if (start_1 <= i_1 && i_1 <= end_1)
			{
				if (find == 0)
				{
					flog2 << "========== "
						  << "SEARCH_BP"
						  << " ==========" << endl;
				}
				i->second->printinfo();
				find = 1;
			}
		}
		cur = cur->getNext();
	}
	if (find == 1)
	{
		flog2 << "=============================" << endl
			  << endl;

		return true;
	}
	else
	{
		flog2 << "========== "
			  << "ERROR"
			  << " ==========" << endl;
		flog2 << "400" << endl;
		flog2 << "===========================" << endl
			  << endl;

		return false;
	}
	flog2.close();
}

bool BpTree::Print()
{
	if (root == NULL)
	{
		return false;
	}
	ofstream flog2; // log.txt
	flog2.open("log.txt", ios::app);

	flog2 << "========== "
		  << "PRINT_BP"
		  << " ==========" << endl;
	BpTreeNode *cur;
	map<string, VaccinationData *>::iterator i;
	cur = root;
	while (cur->getMostLeftChild() != NULL) // go to datanode
	{
		cur = cur->getMostLeftChild();
	}
	while (cur != NULL)
	{
		for (i = cur->getDataMap()->begin(); i != cur->getDataMap()->end(); i++)
		{
			i->second->printinfo();
		}
		cur = cur->getNext();
	}
	flog2 << "===========================" << endl
		  << endl;
	return true;
	flog2.close();
}

int BpTree::IsLeftFirst(string a, string b)
{ // true: 1, false: 0, same:-1

	int minsize = 0;
	char a_1;
	char b_1;
	minsize = min(a.length(), b.length());
	for (int i = 0; i < minsize; i++)
	{
		a_1 = a[i];
		b_1 = b[i];

		if (a_1 < b_1)
		{
			return 1;
		}
		else if (a_1 == b_1)
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
	if (a.length() < b.length())
	{
		return 1;
	}
	else if (a.length() == b.length())
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
void BpTree::deletebp()
{
	if (root == NULL)
	{
		return;
	}
	// delete datanode
	BpTreeNode *cur;
	BpTreeNode *delnode;

	queue<BpTreeNode *> q;
	cur = root;
	q.push(cur);
	while (!q.empty()) // make queue by level order to delte
	{
		cur = q.front();

		if (cur->getMostLeftChild() != NULL) // if indexnode
		{
			q.push(cur->getMostLeftChild());
			if (cur->isdatanode() != true)
			{
				map<string, BpTreeNode *>::iterator it;
				if (cur->getIndexMap() != NULL)
				{
					for (it = cur->getIndexMap()->begin(); it != cur->getIndexMap()->end(); it++)
					{
						if (it->second != NULL)
						{
							q.push(it->second);
						}
					}
				}
			}
		}
		delnode = q.front();
		if (delnode->isdatanode() != true)
		{
			delnode->getIndexMap()->clear();
			delete delnode;
		}

		else
		{
			map<string, VaccinationData *>::iterator itd;
			for (itd = delnode->getDataMap()->begin(); itd != delnode->getDataMap()->end(); itd++)
			{
				if (itd->second != NULL)
				{
					delete itd->second;
					itd->second = NULL;
				}
			}
			delnode->getDataMap()->clear();
			delete delnode;
		}
		q.pop(); // pop
	}
}