#include "Manager.h"
#include "HeaderTable.h"
#include "FPGrowth.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

#define BUFF_SIZE 128
#define freq first
#define food second

using namespace std;

vector<vector<string>> total_list;
vector<pair<int, string>> fre_list;

void Manager::run(const char *command)
{
	fin.open(command);
	fout.open("log.txt");

	if (!fin)
	{
		fout << "File Open Error" << endl;
		return;
	}
	char cmd[BUFF_SIZE] = {};

	while (!fin.eof())
	{
		fin.getline(cmd, BUFF_SIZE);
		char *tmp = strtok(cmd, "\n");
		// char *ch_cr = strrchr(tmp, 13);
		// if (ch_cr)
		// 	*ch_cr = 0;

		if (strcmp(tmp, "LOAD") == 0)
		{
			if (LOAD())
			{
				fout << "==========LOAD==========\nSUCCESS\n========================\n\n";
			}
			else
			{
				fout << "==========LOAD==========\nERROR 100\n========================\n\n";
			}
		}
		else if (strcmp(tmp, "PRINT_ITEMLIST") == 0)
		{
			if (PRINT_ITEMLIST())
			{
				fout << "===========PRINT_ITEMLIST===========\nItem\tFrequency\n";
				for (auto i : fpgrowth->table->indexTable)
				{
					fout << i.second << '\t' << i.first << '\n';
				}
				fout << "================================\n\n";
			}
			else
			{
				fout << "==========PRINT_ITEMLIST==========\nERROR 300\n========================\n\n";
			}
		}
		else if (strcmp(tmp, "PRINT_FPTREE") == 0)
		{
			if (PRINT_FPTREE())
			{
				fout << "================================\n";
			}
			else
			{
				fout << "==========PRINT_FPTREE==========\nERROR 400\n========================\n\n";
			}
		}
		else if (strcmp(tmp, "BTLOAD") == 0)
		{
			if (BTLOAD())
			{
				fout << "==========BTLOAD==========\nSUCCESS\n========================\n\n";
			}
			else
			{
				fout << "==========BTLOAD==========\nERROR 100\n========================\n\n";
			}
		}
	}
	fin.close();
	return;
}

bool Manager::LOAD()
{
	fmarket.open("testcase1");
	if (!fmarket || !total_list.empty())
	{
		return false;
	}
	while (!fmarket.eof())
	{
		char buff[BUFF_SIZE];
		vector<string> tmp_line;
		string index, file_name;

		if (!fmarket.getline(buff, sizeof(buff)))
			break;
		char *tok = strtok(buff, "\t");
		tmp_line.push_back(buff);

		while ((tok = strtok(NULL, "\t")))
		{
			tmp_line.push_back(tok);
		}
		total_list.push_back(tmp_line);

		for (int i = 0; i < tmp_line.size(); i++)
		{
			if (fre_list.empty())
				fre_list.push_back(make_pair(0, tmp_line[i]));
			int j;
			for (j = 0; j < fre_list.size(); j++)
			{
				// tmp_line[i].erase(find(tmp_line.begin(), tmp_line.end(), 13));
				// fre_list[j].food.erase(find(fre_list[j].food.begin(), fre_list[j].food.end(), 13))
				// 여기 카운트제대로안됨
				if (tmp_line[i] == fre_list[j].food)
				{
					fre_list[j].freq++;
					break;
				}
			}
			if (j == fre_list.size())
			{
				fre_list.push_back(make_pair(1, tmp_line[i]));
				break;
			}
		}
	}
	for (int i = 0; i < total_list.size(); i++)
	{
		for (int j = 0; j < total_list[i].size(); j++)
		{
			for (int k = 0; k < fre_list.size(); k++)
			{
				if (total_list[i][j] == fre_list[k].food && fre_list[k].freq < threshold)
					total_list[i].erase(total_list[i].begin() + j);
			}
		}
	}
	for (int i = 0; i < fre_list.size(); i++)
		fpgrowth->createTable(fre_list[i].second, fre_list[i].first);
	fpgrowth->table->descendingIndexTable();
	for (int i = 0; i < total_list.size(); i++)
	{
		for (int j = total_list[i].size() - 1; j > 0; j--)
		{
			for (int k = 0; k < j; k++)
			{
				int m1, m2;
				for (m1 = 0; m1 < fre_list.size(); m1++)
				{

					if (total_list[i][k] == fre_list[m1].food)
						break;
				}
				for (m2 = 0; m2 < fre_list.size(); m2++)
				{
					if (total_list[i][k + 1] == fre_list[m2].food)
						break;
				}
				if (fre_list[m1].freq < fre_list[m2].freq)
				{
					string tmp = total_list[i][k + 1];
					total_list[i][k + 1] = total_list[i][k];
					total_list[i][k] = tmp;
				}
				else if (fre_list[m1].freq == fre_list[m2].freq)
				{
					if (fpgrowth->table->indexTable.begin()->first == max(fpgrowth->table->indexTable.begin()->first, fpgrowth->table->indexTable.end()->first))
					{
						string tmp = total_list[i][k + 1];
						total_list[i][k + 1] = total_list[i][k];
						total_list[i][k] = tmp;
					}
				}
			}
		}
	}
	fpgrowth->createFPtree(fpgrowth->fpTree, fpgrowth->table, total_list);

	return true;
}

bool Manager::BTLOAD()
{

	return true;
}

bool Manager::PRINT_ITEMLIST()
{
	if (!fpgrowth->table)
		return false;
	return true;
}

bool Manager::PRINT_FPTREE()
{
	if (!fpgrowth->fpTree)
		return false;
	fout << "===========PRINT_FPTREE===========\n{StandardItem.Frequency} (Path_Item.Frequency)\n";

	fpgrowth->table->ascendingIndexTable();
	for (auto i : fpgrowth->table->indexTable)
	{
		if (i.first >= threshold)
		{
			fout << "{" << i.second << ", " << i.first << '}' << '\n';
			auto j = fpgrowth->table->dataTable.find(i.second);
			FPNode *cur = j->second;
			while (cur)
			{
				FPNode *par = cur;
				while (par != fpgrowth->fpTree)
				{
					fout << '(';
					for (auto it : par->parent->children)
					{
						if (it.second == par)
							fout << it.first << ", " << par->frequency << ") ";
					}
					par = par->parent;
				}
				fout << '\n';
				cur = cur->next;
			}
		}
	}
	return true;
}

// bool Manager::PRINT_BPTREE(char* item, int min_fre_listquency) {

// }

// bool Manager::PRINT_CONFIDENCE(char* item, double rate) {

// }

// bool Manager::PRINT_RANGE(char* item, int start, int end) {

// }

// void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
// 	// fout << ERROR " << n << " << endl;
// 	fout << "=======================" << endl << endl;
// }

// void Manager::printSuccessCode() {//SUCCESS CODE PRINT
// 	fout << "Success" << endl;
// 	fout << "=======================" << endl << endl;
// }
