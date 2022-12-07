#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph
{
public:
	map<int, int> *m_List;

	ListGraph();
	ListGraph(bool type, int size);
	~ListGraph();

	map<int, int> getAdjacentEdges(int vertex);
	void insertEdge(int from, int to, int weight);
	bool printGraph(ofstream &fout);
};

#endif