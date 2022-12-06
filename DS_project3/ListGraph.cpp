#include "ListGraph.h"
#include "Manager.h"
#include "GraphMethod.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}

map<int, int> ListGraph::getAdjacentEdges(int vertex)
{
	return m_List[vertex];
}

void ListGraph::insertEdge(int from, int to, int weight)
{
	m_List[from].insert({to, weight});
}

bool ListGraph::printGraph(ofstream *ftq)
{
	if (m_List->empty())
		return 0;
	for (int i = 0; i < m_Size; i++)
	{
		*ftq << "[" << i << "]";

		for (auto it_ = m_List[i].begin(); it_ != m_List[i].end() && *ftq << " -> "; it_++)
		{
			*ftq << "(" << it_->first << "," << it_->second << ")";
		}
		*ftq << endl;
	}
	*ftq << endl;
	return 1;
}