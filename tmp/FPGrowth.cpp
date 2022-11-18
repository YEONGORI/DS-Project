#include "FPGrowth.h"

FPGrowth::~FPGrowth()
{
}

void FPGrowth::createFPtree(FPNode *root, HeaderTable *table, vector<vector<string>> item_array)
{
	for (int i = 0; i < item_array.size(); i++)
	{
		FPNode *p = root;
		map<string, FPNode *> cur_node = root->children;
		for (int j = 0; j < item_array[i].size(); j++)
		{
			auto tmp = cur_node.find(item_array[i][j]);
			if (cur_node.empty())
			{
				FPNode *new_node = new FPNode;
				new_node->frequency = 1;
				new_node->parent = p;
				auto exist = table->dataTable.find(item_array[i][j]);
				if (exist == table->dataTable.end())
				{
					table->dataTable.insert({item_array[i][j], new_node});
				}
				else
				{
					FPNode *parent_node = exist->second;
					FPNode *tmp_node = exist->second->next;

					while (tmp_node)
					{
						parent_node = tmp_node;
						tmp_node = tmp_node->next;
					}

					parent_node->next = new_node;
				}
				cur_node.insert(make_pair(item_array[i][j], new_node));
				p->children = cur_node;
				p = new_node;
				cur_node = new_node->children;
			}
			else
			{
				if (tmp != cur_node.end())
				{
					// tmp->second->frequency++;
					p->children[item_array[i][j]]->frequency++;

					p = p->children[item_array[i][j]];
					cur_node = tmp->second->children;
				}
				else
				{
					FPNode *new_node = new FPNode;
					new_node->frequency = 1;
					new_node->parent = p;

					auto exist = table->dataTable.find(item_array[i][j]);
					if (exist == table->dataTable.end())
					{
						table->dataTable.insert({item_array[i][j], new_node});
					}
					else
					{
						FPNode *parent_node = exist->second;
						FPNode *tmp_node = exist->second->next;

						while (tmp_node)
						{
							parent_node = tmp_node;
							tmp_node = tmp_node->next;
						}

						parent_node->next = new_node;
					}

					cur_node.insert(make_pair(item_array[i][j], new_node));
					p->children = cur_node;
					p = new_node;
					cur_node = new_node->children;
				}
			}
		}
	}
}

void FPGrowth::connectNode(HeaderTable *table, string item, FPNode *node)
{
}

bool FPGrowth::contains_single_path(FPNode *pNode)
{
	if (pNode->getChildren().size() == 0)
		return true;
	else if (pNode->getChildren().size() > 1)
		return false;
	return contains_single_path(pNode->getChildren().begin()->second);
}

map<set<string>, int> FPGrowth::getFrequentPatterns(HeaderTable *pTable, FPNode *pTree)
{

	return {};
}

void FPGrowth::powerSet(map<set<string>, int> *FrequentPattern, vector<string> data, string item, int frequency, int *ptr, int depth)
{
	if (data.size() == depth)
	{
		set<string> set;
		set.insert(item);
		for (int i = 0; i < data.size(); i++)
		{
			if (ptr[i] == 1)
				set.insert(data[i]);
		}
		FrequentPattern->insert(make_pair(set, frequency));
		return;
	}
	ptr[depth] = 1;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
	ptr[depth] = 0;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
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
