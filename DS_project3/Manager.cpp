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

	if (!fin)
	{
		fout << "[ERROR] command file open error!" << endl;
		return;
	}

	char *str = NULL;
	char *str2 = NULL;
	char buf[129] = {0};
	char *cmd = NULL;

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
			if (PRINT())
				printSuccessCode();
			else
				printErrorCode(200);
		}
		else if (strcmp(cmd, "BFS") == 0)
		{
			fout << "========BFS=======\n";
			str = strtok(NULL, "\n");
			if (mBFS(stoi(str)))
				printSuccessCode();
			else
				printErrorCode(200);
		}
		else if (strcmp(cmd, "DFS") == 0)
		{
			fout << "========DFS=======\n";
			str = strtok(NULL, "\n");
			if (mDFS(stoi(str)))
				printSuccessCode();
			else
				printErrorCode(200);
		}
		else if (strcmp(cmd, "DFS_R") == 0)
		{
			fout << "========DFS_R=======\n";
			str = strtok(NULL, "\n");
			if (mDFS_R(stoi(str)))
				printSuccessCode();
			else
				printErrorCode(200);
		}
		else if (strcmp(cmd, "KRUSKAL") == 0)
		{
			fout << "========KRUSKAL=======\n";
			if (mKRUSKAL())
				printSuccessCode();
			else
				printErrorCode(200);
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
			}
		}
	}
	fout << "SUCCESS\n"
		 << endl;
	return true;
}

bool Manager::PRINT()
{
	if (graph->printGraph())
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{
	if (BFS(graph, vertex))
		return true;
	return false;
}

bool Manager::mDFS(int vertex)
{
	if (DFS(graph, vertex))
		return true;
	return false;
}

bool Manager::mDFS_R(int vertex)
{
	vector<bool> V;
	for (int i = 0; i < graph->getSize(); i++)
		V.push_back(false);
	if (DFS_R(graph, &V, vertex))
		return true;
	return false;
}

bool Manager::mDIJKSTRA(int vertex)
{

}

bool Manager::mKRUSKAL()
{
	if (Kruskal(graph))
		return true;
	return false;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{
}

bool Manager::mFLOYD()
{
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
