#include <map>
#include <cstring>
#include <iostream>
#include <stdlib.h>

#include "Graph.h"
#include "Manager.h"
#include "ListGraph.h"
#include "GraphMethod.h"

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

	char buf[129] = {0};
	char *cmd = NULL;
	char *str = NULL;
	char *str2 = NULL;

	while (fin.getline(buf, 128))
	{
		cmd = strtok(buf, " \n");
		if (strcmp(cmd, "LOAD") == 0)
		{
			fout << "========LOAD========\n";
			str = strtok(NULL, "\n");
			if (str == NULL)
				printErrorCode(100);

			// if (str == "graph_M.txt")
			if (strcmp(str, "graph_M.txt") == 0)
			{
				fout << "Please input graph_L.txt\n";
				return;
			}
			if (LOAD(str))
				printSuccessCode();
			else
				printErrorCode(100);
		}
		else if (strcmp(cmd, "PRINT") == 0)
		{
			fout << "========PRINT=======\n";
			if (PRINT(fout))
				printSuccessCode();
			else
				printErrorCode(200);
		}
		else if (strcmp(cmd, "BFS") == 0)
		{
			fout << "=========BFS========\n";
			str = strtok(NULL, "\n");
			if (str == NULL) // Check vertex is exist
				printErrorCode(300);

			if (mBFS(stoi(str), fout))
				printSuccessCode();
			else
				printErrorCode(300);
		}
		else if (strcmp(cmd, "DFS") == 0)
		{
			fout << "=========DFS========\n";
			str = strtok(NULL, "\n");
			if (str == NULL) // Check vertex is exist
				printErrorCode(400);
			if (mDFS(stoi(str), fout))
				printSuccessCode();
			else
				printErrorCode(400);
		}
		else if (strcmp(cmd, "DFS_R") == 0)
		{
			fout << "========DFS_R=======\n";
			str = strtok(NULL, "\n");
			if (str == NULL) // Check vertex is exist
				printErrorCode(500);
			if (mDFS_R(stoi(str), fout))
				printSuccessCode();
			else
				printErrorCode(500);
		}
		else if (strcmp(cmd, "KRUSKAL") == 0)
		{
			fout << "=======KRUSKAL======\n";
			if (mKRUSKAL(fout))
				printSuccessCode();
			else
				printErrorCode(600);
		}
		else if (strcmp(cmd, "DIJKSTRA") == 0)
		{
			str = strtok(NULL, "\n");
			fout << "======DIJKSTRA======\n";
			if (str == NULL) // Check vertex is exist
				printErrorCode(700);
			if (mDIJKSTRA(stoi(str), fout))
				printSuccessCode();
			else
				printErrorCode(700);
		}
		else if (strcmp(cmd, "BELLMANFORD") == 0)
		{
			str = strtok(NULL, " ");
			str2 = strtok(NULL, "\n");
			fout << "=====BELLMANFORD====\n";
			if (str == NULL || str2 == NULL) // Check vertex is exist
				printErrorCode(800);
			if (mBELLMANFORD(stoi(str), stoi(str2), fout))
				printSuccessCode();
			else
				printErrorCode(800);
		}
		else if (strcmp(cmd, "FLOYD") == 0)
		{
			fout << "========FLOYD=======\n";
			if (mFLOYD(fout))
				printSuccessCode();
			else
				printErrorCode(900);
		}
		else if (strcmp(cmd, "EXIT") == 0)
		{
			fin.close();
			return;
		}
		memset(buf, 0, 129); // clear buffer
	}
	fin.close();
}

bool Manager::LOAD(char *filename)
{
	int graph_type, graph_size, from, to, weight;
	char buf[129] = {0};
	ifstream fgraph;

	fgraph.open(filename);
	if (!fgraph)
	{
		fout << "[ERROR] command file open error!\n";
		return false;
	}

	fgraph.getline(buf, 128);
	graph_type = (buf[0] == 'M' ? 1 : 0); // Check Matrix or List
	fgraph.getline(buf, 128);
	graph_size = stoi(buf); // Find graph size
	graph = new ListGraph(graph_type, graph_size);

	if (!graph_type)
	{
		while (fgraph.getline(buf, 128)) // Read edges and weight
		{
			char *tmp;
			if (!strchr(buf, ' '))
			{
				from = 0, to = 0, weight = 0;
				from = stoi(buf);
			}
			else
			{
				tmp = strtok(buf, " ");
				to = stoi(tmp);
				tmp = strtok(NULL, "\n");
				weight = stoi(tmp);
				graph->insertEdge(from, to, weight);
				value_checker.push_back(from);
			}
		}
	}
	fout << "SUCCESS\n";
	return true;
}

bool Manager::PRINT(ofstream &fout)
{
	if (graph->printGraph(fout))
		return true;
	return false;
}

bool Manager::mBFS(int vertex, ofstream &fout)
{
	if (find(value_checker.begin(), value_checker.end(), vertex) == value_checker.end()) // Check finding vertex is in the list
		return false;
	if (BFS(graph, vertex, fout))
		return true;
	return false;
}

bool Manager::mDFS(int vertex, ofstream &fout)
{
	if (find(value_checker.begin(), value_checker.end(), vertex) == value_checker.end()) // Check finding vertex is in the list
		return false;
	if (DFS(graph, vertex, fout))
		return true;
	return false;
}

bool Manager::mDFS_R(int vertex, ofstream &fout)
{
	if (find(value_checker.begin(), value_checker.end(), vertex) == value_checker.end()) // Check finding vertex is in the list
		return false;
	vector<bool> vis;
	for (int i = 0; i < graph->getSize(); i++)
		vis.push_back(false);
	if (DFS_R(graph, &vis, vertex, fout))
		return true;
	return false;
}

bool Manager::mKRUSKAL(ofstream &fout)
{
	if (Kruskal(graph, fout))
		return true;
	return false;
}

bool Manager::mDIJKSTRA(int vertex, ofstream &fout)
{
	if (find(value_checker.begin(), value_checker.end(), vertex) == value_checker.end()) // Check finding vertex is in the list
		return false;
	if (Dijkstra(graph, vertex, fout))
		return true;
	return false;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex, ofstream &fout)
{
	if (find(value_checker.begin(), value_checker.end(), s_vertex) == value_checker.end()) // Check finding vertex is in the list
		return false;
	if (Bellmanford(graph, s_vertex, e_vertex, fout))
		return true;
	return false;
}

bool Manager::mFLOYD(ofstream &fout)
{
	if (FLOYD(graph, fout))
		return true;
	return false;
}

void Manager::printSuccessCode(void)
{
	fout << "====================\n\n";
}

void Manager::printErrorCode(int n)
{
	fout << "======= ERROR =======\n";
	fout << n << "\n";
	fout << "=====================\n";
}
