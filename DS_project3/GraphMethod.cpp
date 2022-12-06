#include "GraphMethod.h"
#include "ListGraph.h"
#include <queue>
#include <iostream>
#include <stack>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> iPair;

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
    fstream ftmp("log.txt", ios::app);

    for (int i = 0; i < graph->getSize(); i++)
    {
        parent[i] = i;
    }
    priority_queue<tuple<int, int, int>> edges; // weight, from, to
    map<int, int> m[graph->getSize()];

    for (int i = 0; i < graph->getSize(); i++)
    {
        for (auto it : graph->getAdjacentEdges(i))
        {
            tuple<int, int, int> tmp_tuple = make_tuple((it.second * -1), i, it.first);
            edges.push(tmp_tuple);
        }
    }

    for (int i = 0; i < graph->getSize() && !edges.empty(); i++)
    {
        tuple<int, int, int> tmp = edges.top();
        edges.pop(); // delete
        if (!check_same_parent(parent, get<1>(tmp), get<2>(tmp)))
        {
            union_parent(parent, get<1>(tmp), get<2>(tmp));
            sum += get<0>(tmp) * -1;
            m[get<1>(tmp)].insert({get<2>(tmp), get<0>(tmp)});
            m[get<2>(tmp)].insert({get<1>(tmp), get<0>(tmp)});
        }
    }
    for (int i = 0; i < graph->getSize() && !edges.empty(); i++)
    {
        ftmp << "[" << i << "] ";
        for (auto t : m[i])
        {
            ftmp << t.first << "(" << t.second * -1 << ") ";
        }
        ftmp << "\n";
    }

    ftmp << "cost: " << sum << "\n";
    ftmp.close();
}
// 명령어의 결과인 shortest path와 cost를 출력 파일(log.txt)에 출력한다
// 출력 시 vertex, shortest path, cost 순서로 출력하며, shortest path는
// 해당 vertex에서 기준 vertex까지의 경로를 역순으로 출력한다
// 기준 vertex에서 도달할 수 없는 vertex의 경우 ‘x’를 출력한다.
bool Dijkstra(Graph *graph, int vertex)
{
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    fstream ftmp("log.txt", ios::app);

    vector<int> dist(graph->getSize(), INFINITY);
    int prev[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++)
        prev[i] = i;
    pq.push(make_pair(0, vertex));
    ftmp << "startvertex: " << vertex << "\n";
    dist[vertex] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (auto i : graph->getAdjacentEdges(u))
        {
            int v = i.first;
            int weight = i.second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                prev[v] = u;
            }
        }
    }
    for (int i = 0; i < graph->getSize(); i++)
    {
        if (i == vertex)
            continue;
        ftmp << "[" << i << "] ";
        int j = i;
        if (prev[j] != j)
        {
            stack<int> S;
            while (prev[i] != vertex)
            {
                S.push(prev[i]);
                i = prev[i];
            }
            ftmp << vertex << " -> ";
            while (!S.empty())
            {
                ftmp << S.top() << " -> ";
                S.pop();
            }
            ftmp << j << " (" << dist[j] << ")\n";
        }
        else
            ftmp << "x\n";
        i = j;
    }
    ftmp.close();
}

bool Bellmanford(Graph *graph, int s_vertex, int e_vertex)
{
    int dist[graph->getSize()];
    int prev[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++)
    {
        prev[i] = i;
        dist[i] = 214748364;
    }
    dist[s_vertex] = 0;
    fstream ftmp("log.txt", ios::app);

    for (auto adj : graph->getAdjacentEdges(s_vertex))
    {
        dist[adj.first] = adj.second;
    }
    map<int, int> incoming[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++) // incomming
    {
        for (auto it : graph->getAdjacentEdges(i))
        {
            incoming[it.first].insert({i, it.second});
        }
    }
    for (int k = 2; k <= graph->getSize() - 1; k++)
    {
        for (int v = 0; v < graph->getSize(); v++)
        {
            if (v == s_vertex && incoming[v].empty())
                continue;
            for (int w = 0; w < graph->getSize(); w++)
            {
                if (w == v && graph->getAdjacentEdges(w).find(v) == graph->getAdjacentEdges(w).end())
                    continue;
                if (dist[v] > dist[w] + graph->getAdjacentEdges(w).find(v)->second)
                {
                    dist[v] = dist[w] + graph->getAdjacentEdges(w).find(v)->second;
                    prev[v] = w;
                }
            }
        }
    }

    stack<int> S;
    int end = e_vertex;
    while (prev[e_vertex] != s_vertex)
    {
        S.push(prev[e_vertex]);
        e_vertex = prev[e_vertex];
    }
    ftmp << s_vertex << " -> ";
    while (!S.empty())
    {
        ftmp << S.top() << " -> ";
        S.pop();
    }
    ftmp << "cost: " << dist[end] << "\n";
    ftmp.close();
}

bool FLOYD(Graph *graph)
{
    int A[graph->getSize()][graph->getSize()];

    for (int k = 1; k <= graph->getSize(); k++)
    {
        for (int i = 1; i <= graph->getSize(); i++)
        {
            for (int j = 1; j <= graph->getSize(); j++)
            {
                A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
            }
        }
    }
}