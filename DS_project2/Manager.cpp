#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "BpTree.h"
#include "Manager.h"
#include "FPGrowth.h"
#include "BpTreeNode.h"
#include "HeaderTable.h"
#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "FrequentPatternNode.h"

using namespace std;

void Manager::run(const char *command)
{
	fin.open(command);
	fout.open("log.txt");

	char cmd[100] = {};
	if (!fin)
	{
		fout << "File Open Error" << endl;
		return;
	}

	while (!fin.eof())
	{
		fin.getline(cmd, 100);
		char *tmp = strtok(cmd, " ");

		if (strcmp(tmp, "LOAD") == 0) // Execute LOAD
		{
			fout << "=============LOAD============\n";
			if (LOAD())
				printSuccessCode();
			else
				printErrorCode(100);
		}
		else if (strcmp(tmp, "BTLOAD") == 0) // Execute BTROAD
		{
			fout << "============BTLOAD============\n";
			if (BTLOAD())
				printSuccessCode();
			else
				printErrorCode(200);
		}
		else if (strcmp(tmp, "PRINT_ITEMLIST") == 0) // Execute PRINT_ITEMLIST
		{
			fout << "=========PRINT_ITEMLIST========\n";
			if (PRINT_ITEMLIST())
				fout << "=================================\n\n";
			else
				printErrorCode(300);
		}
		else if (strcmp(tmp, "PRINT_FPTREE") == 0) // Execute PRINT_FPTREE
		{
			fout << "==========PRINT_FPTREE==========\n";
			if (PRINT_FPTREE())
				fout << "=================================\n\n";
			else
				printErrorCode(400);
		}
		else if (strcmp(tmp, "PRINT_BPTREE") == 0) // Execute PRINT_BRTREE
		{
			char *item_name = strtok(NULL, " ");
			char *item_freq = strtok(NULL, " ");
			fout << "==========PRINT_BPTREE==========\n";
			if (!item_name || !item_freq)
			{
				printErrorCode(500);
				continue;
			}
			if (PRINT_BPTREE(item_name, stoi(item_freq)))
				fout << "=================================\n\n";
			else
				printErrorCode(500);
		}
		else if (strcmp(tmp, "PRINT_CONFIDENCE") == 0) // Execute PRINT_CONFIDENCE
		{
			char *item_name = strtok(NULL, " ");
			char *item_freq = strtok(NULL, " ");
			fout << "=========PRINT_CONFIDENCE=========\n";
			if (!item_freq || !strchr(item_freq, '.'))
			{
				printErrorCode(600);
				continue;
			}
			if (PRINT_CONFIDENCE(item_name, stod(item_freq)))
				fout << "=================================\n\n";
			else
				printErrorCode(600);
		}
		else if (strcmp(tmp, "PRINT_RANGE") == 0) // Execute PRINT_RANGE
		{
			char *item_name = strtok(NULL, " ");
			char *start = strtok(NULL, " ");
			char *end = strtok(NULL, " ");

			fout << "==========PRINT_RANGE==========\n";
			if (item_name == NULL || start == NULL || end == NULL || strchr(start, '.') || strchr(end, '.'))
			{
				printErrorCode(700);
				continue;
			}
			if (PRINT_RANGE(item_name, stoi(start), stoi(end)))
				fout << "=================================\n\n";
			else
				printErrorCode(700);
		}
		else if (strcmp(tmp, "EXIT") == 0)
		{
			fout << "=============EXIT==============\n";
			printSuccessCode();
		}
	}
	fin.close();
	return;
}

bool Manager::LOAD()
{
	int item_prev, item_next;
	string temp;

	vector<pair<int, string>> freq_item;
	vector<vector<string>> freq_item_total;
	fmarket.open("market.txt");
	if (!fmarket || fpgrowth->fpTree->fp_count > 0)
		return false;

	while (!fmarket.eof())
	{
		int flag;
		char buf_temp[128];
		char *item_tok;
		vector<string> item_temp;

		if (!fmarket.getline(buf_temp, sizeof(buf_temp)))
			break;
		item_tok = strtok(buf_temp, "\t");
		item_temp.push_back(buf_temp);

		while ((item_tok = strtok(NULL, "\t"))) // Get item
			item_temp.push_back(item_tok);
		freq_item_total.push_back(item_temp);

		for (int i = 0; i < item_temp.size(); i++) // Calculate the item and frequency.
		{
			if (freq_item.empty())
				freq_item.push_back(make_pair(0, item_temp[i]));
			flag = 0;
			for (int j = 0; j < freq_item.size(); j++)
			{
				if (item_temp[i] == freq_item[j].second)
				{
					freq_item[j].first++;
					flag = 1;
					break;
				}
			}
			if (flag == 0)
				freq_item.push_back(make_pair(1, item_temp[i]));
		}
	}
	for (int i = 0; i < freq_item_total.size(); i++) // Remove items with frequency less than threshold
	{
		for (int j = 0; j < freq_item_total[i].size(); j++)
		{
			for (int k = 0; k < freq_item.size(); k++)
			{
				if (j >= freq_item_total[i].size())
					break;
				if (freq_item_total[i][j] == freq_item[k].second && freq_item[k].first < threshold)
					freq_item_total[i].erase(freq_item_total[i].begin() + j);
			}
		}
	}
	for (int i = 0; i < freq_item.size(); i++) // Create ftree Node with created frequency and item list
		fpgrowth->createTable(freq_item[i].second, freq_item[i].first);
	fpgrowth->table->descendingIndexTable();
	// fpgrowth->table->ascendingIndexTable();

	for (int i = 0; i < freq_item_total.size(); i++) // Sort created lists in descending order
	{
		for (int j = freq_item_total[i].size() - 1; j > 0; j--) // Buble sort
		{
			for (int k = 0; k < j; k++)
			{
				for (item_prev = 0; item_prev < freq_item.size(); item_prev++)
				{
					if (freq_item_total[i][k] == freq_item[item_prev].second)
						break;
				}
				for (item_next = 0; item_next < freq_item.size(); item_next++)
				{
					if (freq_item_total[i][k + 1] == freq_item[item_next].second)
						break;
				}
				if (freq_item[item_prev].first < freq_item[item_next].first)
				{
					temp = freq_item_total[i][k + 1];
					freq_item_total[i][k + 1] = freq_item_total[i][k];
					freq_item_total[i][k] = temp;
				}
			}
		}
	}
	fpgrowth->createFPtree(fpgrowth->fpTree, fpgrowth->table, freq_item_total); // Create FP Tree

	return true;
}

bool Manager::BTLOAD()
{
	fresult.open("result.txt");
	if (!fresult && bptree->node_count > 0)
		return false;

	while (!fresult.eof())
	{
		int frequency;
		char item[100];
		char *item_tmp;
		set<string> food_list;

		if (!fresult.getline(item, sizeof(item)))
			break;

		item_tmp = strtok(item, "\t");
		frequency = stoi(item_tmp);
		while ((item_tmp = strtok(NULL, "\t"))) // Insert each frequent pattern
			food_list.insert(item_tmp);

		bptree->Insert(frequency, food_list); // Insert BP Tree
		BpTreeNode *cur_bptree_node = bptree->root;
		while (cur_bptree_node->getMostLeftChild()) // Find Data node
			cur_bptree_node = cur_bptree_node->getMostLeftChild();

		while (cur_bptree_node) // Verify that the number of blocks nodes exceeds the order
		{
			if (bptree->excessDataNode(cur_bptree_node))
				bptree->splitDataNode(cur_bptree_node);
			cur_bptree_node = cur_bptree_node->getNext();
		}
	}
	return true;
}

bool Manager::PRINT_ITEMLIST()
{
	if (fpgrowth->getHeaderTable()->getindexTable().empty())
		return false;
	fout << "Item\tFrequency\n";
	for (auto i : fpgrowth->table->indexTable) // Print All Item
		fout << i.second << ' ' << i.first << '\n';
	return true;
}

bool Manager::PRINT_FPTREE()
{
	if (fpgrowth->getTree()->getChildren().empty())
		return false;

	fout << "{StandardItem.Frequency} (Path_Item.Frequency)\n";

	fpgrowth->table->ascendingIndexTable();
	for (auto standard_item : fpgrowth->table->indexTable) // Travelling repeat statements for each of the entire items
	{
		if (standard_item.first >= threshold) // Check item threshold
		{
			fout << "{" << standard_item.second << ", " << standard_item.first << "}"
				 << "\n";
			auto cur_item = fpgrowth->table->dataTable.find(standard_item.second);
			FPNode *cur_fp_node = cur_item->second;
			while (cur_fp_node) // Check all nodes including the current item
			{
				FPNode *par_fp_node = cur_fp_node;
				while (par_fp_node != fpgrowth->fpTree)
				{
					fout << "(";
					for (auto path_item : par_fp_node->parent->children)
					{
						if (path_item.second == par_fp_node)
							fout << path_item.first << ", " << par_fp_node->frequency;
					}
					fout << ") ";
					par_fp_node = par_fp_node->parent;
				}
				fout << "\n";
				cur_fp_node = cur_fp_node->next;
			}
		}
	}
	return true;
}

bool Manager::PRINT_BPTREE(char *item, int item_freq)
{
	if (item == NULL || bptree->node_count == 0)
		return false;

	int flag = 0;
	string item_name = item;
	BpTreeNode *condition_pos = bptree->searchDataNode(item_freq); // Search for data nodes that satisfy frequency

	fout << "FrequentPattern Frequency\n";
	while (condition_pos->getNext()) // Travelling all BP Tree Nodes
	{
		auto data_node = condition_pos->getDataMap();
		for (auto cur_data_node = data_node->begin(); cur_data_node != data_node->end(); cur_data_node++) // Travelling all Data Nodes
		{
			if (cur_data_node->first >= item_freq)
			{
				auto cur_freq_pat_node = cur_data_node->second->getList();
				for (auto freq_pat_node = cur_freq_pat_node.begin(); freq_pat_node != cur_freq_pat_node.end(); freq_pat_node++) // Travelling all frequenct pattern nodes
				{
					auto item_set = freq_pat_node->second;
					auto res = item_set.find(item_name);
					if (res != item_set.end())
					{
						fout << "{";
						for (auto cur_item = item_set.begin(); cur_item != item_set.end(); cur_item++) // Travelling all item set
						{
							fout << *cur_item++;
							if (cur_item != item_set.end())
								fout << ", ";
							cur_item--;
						}
						fout << "} " << cur_data_node->first << "\n";
						flag = 1;
					}
				}
			}
		}
		condition_pos = condition_pos->getNext();
	}
	if (flag == 0)
		return false;
	return true;
}

bool Manager::PRINT_CONFIDENCE(char *item, double rate)
{
	if (item == NULL || bptree->node_count == 0)
		return false;

	fout << "FrequentPattern Frequency Confidence\n";

	int item_freq = 0, flag = 0;
	string item_name = item;
	BpTreeNode *data_node = bptree->root;

	for (auto cur_item = fpgrowth->getHeaderTable()->indexTable.begin(); cur_item != fpgrowth->getHeaderTable()->indexTable.end(); cur_item++) // Search items frequency
	{
		if (cur_item->second == item_name)
		{
			item_freq = cur_item->first;
			break;
		}
	}

	while (data_node->getMostLeftChild()) // Find Data Node
		data_node = data_node->getMostLeftChild();

	while (data_node->getNext()) // Travelling All Bp Tree Node
	{
		auto cur_data_node = data_node->getDataMap();
		for (auto freq_pat_node = cur_data_node->begin(); freq_pat_node != cur_data_node->end(); freq_pat_node++)
		{
			if ((double)freq_pat_node->first / item_freq > rate) // Check that the ratio meets the conditions in question
			{
				auto cur_freq_pat_node = freq_pat_node->second->getList();
				for (auto item_set = cur_freq_pat_node.begin(); item_set != cur_freq_pat_node.end(); item_set++) // Travelling all item set
				{
					if (item_set->second.find(item_name) != item_set->second.end())
					{
						auto cur_item_set = item_set->second;
						fout << "{";
						for (auto cur_item = cur_item_set.begin(); cur_item != cur_item_set.end(); cur_item++) // Travelling all item
						{
							fout << *cur_item++;
							if (cur_item != cur_item_set.end())
								fout << ", ";
							cur_item--;
						}
						flag = 1;
						fout << "} " << freq_pat_node->first << " " << ((double)freq_pat_node->first / item_freq) << "\n";
					}
				}
			}
		}
		data_node = data_node->getNext();
	}
	if (flag == 0)
		return false;
	return true;
}

bool Manager::PRINT_RANGE(char *item, int start, int end)
{
	if (item == NULL || bptree->node_count == 0)
		return false;

	fout << "FrequentPattern Frequency Confidence\n";

	int flag = 0;
	string item_name = item;
	BpTreeNode *condition_pos = bptree->searchDataNode(start);
	condition_pos->getDataMap()->begin()->second;
	while (condition_pos->getNext()) // Travelling all data nodes
	{
		auto data_node = condition_pos->getDataMap();
		for (auto cur_data_node = data_node->begin(); cur_data_node != data_node->end(); cur_data_node++) // Travelling all frequent pattern node
		{
			if (cur_data_node->first >= start && cur_data_node->first <= end) // Check conditions frequency
			{
				auto cur_freq_pat_node = cur_data_node->second->getList();
				for (auto item_set = cur_freq_pat_node.begin(); item_set != cur_freq_pat_node.end(); item_set++) // Travelling all item set
				{
					auto cur_item_set = item_set->second;
					auto ch = cur_item_set.find(item_name);
					if (ch != cur_item_set.end())
					{
						flag = 1;
						fout << "{";
						for (auto cur_item = cur_item_set.begin(); cur_item != cur_item_set.end(); cur_item++) // Travelling all item
						{
							fout << *cur_item++;
							if (cur_item != cur_item_set.end())
								fout << ", ";
							cur_item--;
						}
						fout << "} " << cur_data_node->first << "\n";
					}
				}
			}
		}
		condition_pos = condition_pos->getNext();
	}
	if (flag == 0)
		return false;
	return true;
}

void Manager::printErrorCode(int n)
{ // ERROR CODE PRINT
	fout << "ERROR " << n << "\n";
	fout << "===========================\n\n";
}

void Manager::printSuccessCode()
{ // SUCCESS CODE PRINT
	fout << "Success\n";
	fout << "===========================\n\n";
}