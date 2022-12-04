#include "GraphMethod.h"
#include "ListGraph.h"
#include <queue>
#include <iostream>
#include <stack>

using namespace std;

bool BFS(Graph *graph, int vertex)
{
    fstream ftmp("log.txt", ios::app);
    queue<int> QU;
    int vis[graph->getSize() + 1] = {0};
    int cnt = 1;

    QU.push(vertex);
    vis[vertex] = 1;
    ftmp << "startvertex: " << vertex << "\n";
    ftmp << vertex << " -> ";
    while (!QU.empty())
    {
        auto cur = QU.front();
        QU.pop();
        for (auto edges : graph->getAdjacentEdges(cur))
        {
            if (vis[edges.first])
                continue;
            vis[edges.first] = 1;
            QU.push(edges.first);
            ftmp << edges.first;
            if (++cnt < graph->getSize())
                ftmp << " -> ";
        }
    }
    ftmp << "\n";
    ftmp.close();
    return true;
}

bool DFS(Graph *graph, int vertex)
{
    fstream ftmp("log.txt", ios::app);
    stack<int> ST;
    int vis[graph->getSize() + 1] = {0};
    int cnt = 1;

    ST.push(vertex);
    vis[vertex] = 1;
    ftmp << "startvertex: " << vertex << "\n";
    while (!ST.empty())
    {
        auto cur = ST.top();
        ST.pop();
        ftmp << cur;
        if (cnt++ < graph->getSize())
            ftmp << " -> ";
        for (auto edges : graph->getAdjacentEdges(cur))
        {
            if (vis[edges.first])
                continue;
            ST.push(edges.first);
            vis[edges.first] = 1;
        }
    }
    ftmp << "\n";
    ftmp.close();
    return true;
}

bool DFS_R(Graph *graph, vector<bool> *visit, int vertex)
{
    visit[0][vertex] = true;
    fstream ftmp("log.txt", ios::app);
    ftmp << vertex << " ";
    ftmp.close();
    for (auto edges : graph->getAdjacentEdges(vertex))
    {
        if (!visit[0][edges.first])
            DFS_R(graph, visit, edges.first);
    }
}

bool Kruskal(Graph *graph)
{
}

bool Dijkstra(Graph *graph, int vertex)
{
}

bool Bellmanford(Graph *graph, int s_vertex, int e_vertex)
{
}

bool FLOYD(Graph *graph)
{
}