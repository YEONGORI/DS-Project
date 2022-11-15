#include "HeaderTable.h"

HeaderTable::~HeaderTable()
{
}

void HeaderTable::insertTable(string item, int frequency)
{
	indexTable.push_back(make_pair(frequency, item));
}

void HeaderTable::insertDataTable(string item, FPNode *fp)
{
	dataTable.insert({item, fp});
}

int HeaderTable::find_frequency(string item)
{
	int frequency = 0;
	return frequency;
}
