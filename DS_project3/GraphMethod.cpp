#include "GraphMethod.h"
#include "ListGraph.h"
#include <queue>
#include <iostream>
#include <stack>
#include <tuple>
#include <bits/stdc++.h>

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

int find_parent(int *parent, int x)
{
    if (parent[x] == x)
        return x;
    else
        return parent[x] = find_parent(parent, parent[x]);
}
bool check_same_parent(int *parent, int x, int y)
{
    x = find_parent(parent, x);
    y = find_parent(parent, y);

    if (x == y)
        return true;
    else
        return false;
}

void union_parent(int *parent, int x, int y)
{
    x = find_parent(parent, x);
    y = find_parent(parent, y);
    if (x < y)
        parent[y] = x;
    else
        parent[x] = y;
}

bool Kruskal(Graph *graph)
{
    int sum = 0;
    int *parent = new int[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++)
    {
        parent[i] = i;
    }
    priority_queue<int, int, int> edges; // weight, from, to
    for (int i = 0; i < graph->getSize(); i++)
    {
        for (auto it : graph->getAdjacentEdges(i))
        {
            tuple<int, int, int> tmp_tuple = make_tuple((it.second * -1), i, it.first);
            edges.push(tmp_tuple);
        }
    }

    for (int i = 0; i < graph->getSize() && edges.empty(); i++)
    {
        tuple<int, int, int> tmp = edges.top();
        edges.pop(); // delete
        if (!check_same_parent(parent, get<1>(tmp), get<2>(tmp)))
        {
            union_parent(parent, get<1>(tmp), get<2>(tmp));
            sum += get<0>(tmp) * -1;
        }
        cout << "[" << i << "]" << get<2>(tmp) << "(" << get<0>(tmp) * -1 << ")"
             << "\n";
    }
    cout << "cost: " << sum << "\n";
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