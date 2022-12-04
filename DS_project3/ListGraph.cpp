#include "ListGraph.h"

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

bool ListGraph::printGraph()
{
	fstream ftmp("log.txt", ios::app);
	for (int i = 0; i < m_Size; i++)
	{
		ftmp << "[" << i << "]";

		for (auto it_ = m_List[i].begin(); it_ != m_List[i].end() && ftmp << " -> "; it_++)
		{
			ftmp << "(" << it_->first << "," << it_->second << ")";
		}
		ftmp << endl;
	}
	ftmp << endl;
	ftmp.close();
	return 1;
}