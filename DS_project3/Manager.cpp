#include "Manager.h"
#include "Graph.h"
#include "ListGraph.h"
#include "GraphMethod.h"
#include <cstring>
#include <stdlib.h>
#include <map>

using namespace std;

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if (load)
		delete graph;
	fout.close();
}

void Manager::run(const char *command_txt)
{
	ifstream fin;
	fin.open(command_txt);
	fetch1(&fout);
	if (!fin)
	{
		fout << "[ERROR] command file open error!" << endl;
		return;
	}

	char buf[129] = {0};
	char *cmd = NULL;
	char *str = NULL;
	char *str2 = NULL;

	while (fin.getline(buf, 128))
	{
		cmd = strtok(buf, " \n");
		if (strcmp(cmd, "LOAD") == 0)
		{
			fout << "=======LOAD=======\n";
			if (LOAD("graph.txt"))
				printSuccessCode();
			else
				printErrorCode(100);
		}
		else if (strcmp(cmd, "PRINT") == 0)
		{
			fout << "=======PRINT======\n";
			if (PRINT(&fout))
				printSuccessCode();
			else
				printErrorCode(200);
		}
		else if (strcmp(cmd, "BFS") == 0)
		{
			fout << "========BFS=======\n";
			str = strtok(NULL, "\n");
			if (str == NULL)
				printErrorCode(300);
			if (mBFS(stoi(str)))
				printSuccessCode();
			else
				printErrorCode(300);
		}
		else if (strcmp(cmd, "DFS") == 0)
		{
			fout << "========DFS=======\n";
			str = strtok(NULL, "\n");
			if (str == NULL)
				printErrorCode(400);
			if (mDFS(stoi(str)))
				printSuccessCode();
			else
				printErrorCode(400);
		}
		else if (strcmp(cmd, "DFS_R") == 0)
		{
			fout << "========DFS_R=======\n";
			str = strtok(NULL, "\n");
			if (str == NULL)
				printErrorCode(500);
			if (mDFS_R(stoi(str)))
				printSuccessCode();
			else
				printErrorCode(500);
		}
		else if (strcmp(cmd, "KRUSKAL") == 0)
		{
			fout << "========KRUSKAL=======\n";
			if (mKRUSKAL())
				printSuccessCode();
			else
				printErrorCode(600);
		}
		else if (strcmp(cmd, "DIJKSTRA") == 0)
		{
			str = strtok(NULL, "\n");
			fout << "========DIJKSTRA=======\n";
			if (str == NULL)
				printErrorCode(700);
			if (mDIJKSTRA(stoi(str)))
				printSuccessCode();
			else
				printErrorCode(700);
		}
		else if (strcmp(cmd, "BELLMANFORD") == 0)
		{
			str = strtok(NULL, " ");
			str2 = strtok(NULL, "\n");
			fout << "========BELLMANFORD=======\n";
			if (str == NULL || str2 == NULL)
				printErrorCode(800);
			if (mBELLMANFORD(stoi(str), stoi(str2)))
				printSuccessCode();
			else
				printErrorCode(800);
		}
		else if (strcmp(cmd, "FLOYD") == 0)
		{
			fout << "========FLOYD=======\n";
			if (mFLOYD())
				printSuccessCode();
			else
				printErrorCode(900);
		}
		else if (strcmp(cmd, "EXIT") == 0)
		{
		}
		memset(buf, 0, 129);
	}

	fin.close();
}

bool Manager::LOAD(char *filename)
{
	char buffer[129] = {0};
	ifstream fload;
	fload.open(filename);
	if (!fload)
	{
		fout << "[ERROR] command file open error!" << endl;
		return false;
	}
	fload.getline(buffer, 128);
	int graph_type = (buffer[0] == 'M' ? 1 : 0);
	fload.getline(buffer, 128);
	int graph_size = stoi(buffer);
	graph = new ListGraph(graph_type, graph_size);
	if (!graph_type)
	{
		char *tok;
		int from, to, weight;
		while (fload.getline(buffer, 128))
		{
			if (!strchr(buffer, ' '))
			{
				from = 0, to = 0, weight = 0;
				from = stoi(buffer);
			}
			else
			{
				tok = strtok(buffer, " ");
				to = stoi(tok);
				tok = strtok(NULL, "\n");
				weight = stoi(tok);
				graph->insertEdge(from, to, weight);
				store.push_back(from);
			}
		}
	}
	fout << "SUCCESS\n"
		 << endl;
	return true;
}

bool Manager::PRINT(ofstream *fout)
{
	if (graph->printGraph(fout))
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{
	if (find(store.begin(), store.end(), vertex) == store.end())
		return false;
	if (BFS(graph, vertex))
		return true;
	return false;
}

bool Manager::mDFS(int vertex)
{
	if (find(store.begin(), store.end(), vertex) == store.end())
		return false;
	if (DFS(graph, vertex))
		return true;
	return false;
}

bool Manager::mDFS_R(int vertex)
{
	if (find(store.begin(), store.end(), vertex) == store.end())
		return false;
	vector<bool> V;
	for (int i = 0; i < graph->getSize(); i++)
		V.push_back(false);
	if (DFS_R(graph, &V, vertex))
		return true;
	return false;
}

bool Manager::mDIJKSTRA(int vertex)
{
	if (find(store.begin(), store.end(), vertex) == store.end())
		return false;
	if (Dijkstra(graph, vertex))
		return true;
	return false;
}

bool Manager::mKRUSKAL()
{
	if (Kruskal(graph))
		return true;
	return false;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{
	if (find(store.begin(), store.end(), s_vertex) == store.end())
		return false;
	if (Bellmanford(graph, s_vertex, e_vertex))
		return true;
	return false;
}

bool Manager::mFLOYD()
{
	if (FLOYD(graph))
		return true;
	return false;
}

void Manager::printSuccessCode(void)
{
	fout << "=======================\n"
		 << endl;
}

void Manager::printErrorCode(int n)
{
	fout << "======== ERROR ========" << endl;
	fout << n << endl;
	fout << "=======================" << endl;
}
