#include "FPGrowth.h"

FPGrowth::~FPGrowth()
{
}

void FPGrowth::createFPtree(FPNode *root, HeaderTable *table, vector<vector<string>> total_item)
{
	FPNode *fp_node, *par_node, *temp_node;
	map<string, FPNode *> cur_fp_node;
	for (int i = 0; i < total_item.size(); i++) // Travelling total Item that provided from testcase
	{
		fp_node = root;
		cur_fp_node = root->children;
		for (int j = 0; j < total_item[i].size(); j++) // Travelling all fp node
		{
			auto tmp = cur_fp_node.find(total_item[i][j]);
			if (cur_fp_node.empty()) // Check FP Tree has Node
			{
				FPNode *new_fp_node = new FPNode;
				new_fp_node->frequency = 1;
				new_fp_node->parent = fp_node;
				auto cur_item = table->dataTable.find(total_item[i][j]);
				if (cur_item == table->dataTable.end()) // Check cur item already exist in FP Tree
					table->dataTable.insert({total_item[i][j], new_fp_node});
				else
				{
					par_node = cur_item->second;
					temp_node = cur_item->second->next;
					while (temp_node)
					{
						par_node = temp_node;
						temp_node = temp_node->next;
					}
					par_node->next = new_fp_node;
				}
				cur_fp_node.insert(make_pair(total_item[i][j], new_fp_node));
				fpTree->fp_count++;
				fp_node->children = cur_fp_node;
				fp_node = new_fp_node;
				cur_fp_node = new_fp_node->children;
				new_fp_node = NULL;
				delete new_fp_node;
			}
			else
			{
				if (tmp != cur_fp_node.end()) // Check current fp node already exist
				{
					fp_node->children[total_item[i][j]]->frequency++;
					fp_node = fp_node->children[total_item[i][j]];
					cur_fp_node = tmp->second->children;
				}
				else
				{
					FPNode *new_fp_node = new FPNode;
					new_fp_node->frequency = 1;
					new_fp_node->parent = fp_node;

					auto cur_item = table->dataTable.find(total_item[i][j]);
					if (cur_item == table->dataTable.end()) // Check current item already exist
					{
						table->dataTable.insert({total_item[i][j], new_fp_node});
						fpTree->fp_count++;
					}
					else
					{
						par_node = cur_item->second;
						temp_node = cur_item->second->next;
						while (temp_node)
						{
							par_node = temp_node;
							temp_node = temp_node->next;
						}
						par_node->next = new_fp_node;
					}
					cur_fp_node.insert(make_pair(total_item[i][j], new_fp_node));
					fpTree->fp_count++;
					fp_node->children = cur_fp_node;
					fp_node = new_fp_node;
					cur_fp_node = new_fp_node->children;
					new_fp_node = NULL;
					delete new_fp_node;
				}
			}
		}
	}
}

void FPGrowth::connectNode(HeaderTable *table, string item, FPNode *node)
{
	return;
}

bool FPGrowth::contains_single_path(FPNode *pNode)
{
}

map<set<string>, int> FPGrowth::getFrequentPatterns(HeaderTable *pTable, FPNode *pTree)
{
	return {};
}

void FPGrowth::powerSet(map<set<string>, int> *FrequentPattern, vector<string> data, string item, int frequency, int *ptr, int depth)
{
	return;
}

bool FPGrowth::printList()
{
	return true;
}
bool FPGrowth::printTree()
{
	return true;
}
void FPGrowth::saveFrequentPatterns()
{
}
