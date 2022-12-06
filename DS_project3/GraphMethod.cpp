#include "GraphMethod.h"
#include "ListGraph.h"
#include <queue>
#include <iostream>
#include <stack>
#include <tuple>

using namespace std;

typedef pair<int, int> iPair;

ofstream *ffff;

void fetch1(ofstream *of)
{
    ffff = of;
}

bool BFS(Graph *graph, int vertex)
{
    queue<int> QU;
    int vis[graph->getSize() + 1] = {0};
    int cnt = 1;

    QU.push(vertex);
    vis[vertex] = 1;
    *ffff << "startvertex: " << vertex << "\n";
    *ffff << vertex << " -> ";
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
            *ffff << edges.first;
            if (++cnt < graph->getSize())
                *ffff << " -> ";
        }
    }
    *ffff << "\n";
    return true;
}

bool DFS(Graph *graph, int vertex)
{
    stack<int> ST;
    int vis[graph->getSize() + 1] = {0};
    int cnt = 1;

    ST.push(vertex);
    vis[vertex] = 1;
    *ffff << "startvertex: " << vertex << "\n";
    while (!ST.empty())
    {
        auto cur = ST.top();
        ST.pop();
        *ffff << cur;
        if (cnt++ < graph->getSize())
            *ffff << " -> ";
        for (auto edges : graph->getAdjacentEdges(cur))
        {
            if (vis[edges.first])
                continue;
            ST.push(edges.first);
            vis[edges.first] = 1;
        }
    }
    *ffff << "\n";
    return true;
}

int a = 1;
bool DFS_R(Graph *graph, vector<bool> *visit, int vertex)
{
    visit[0][vertex] = true;
    *ffff << vertex;
    a++;
    if (a < graph->getSize())
        *ffff << " -> ";
    else
        *ffff << "\n";
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
    if (sum < 0)
        return false;
    for (int i = 0; i < graph->getSize() && !edges.empty(); i++)
    {
        *ffff << "[" << i << "] ";
        for (auto t : m[i])
        {
            *ffff << t.first << "(" << t.second * -1 << ") ";
        }
        *ffff << "\n";
    }

    *ffff << "cost: " << sum << "\n";
    return true;
}

bool Dijkstra(Graph *graph, int vertex)
{
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    vector<int> dist(graph->getSize(), INFINITY);
    int prev[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++)
        prev[i] = i;
    pq.push(make_pair(0, vertex));
    *ffff << "startvertex: " << vertex << "\n";
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
        *ffff << "[" << i << "] ";
        int j = i;
        if (prev[j] != j)
        {
            stack<int> S;
            while (prev[i] != vertex)
            {
                S.push(prev[i]);
                i = prev[i];
            }
            *ffff << vertex << " -> ";
            while (!S.empty())
            {
                *ffff << S.top() << " -> ";
                S.pop();
            }
            *ffff << j << " (" << dist[j] << ")\n";
        }
        else
            *ffff << "x\n";
        i = j;
    }
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

    for (auto adj : graph->getAdjacentEdges(s_vertex))
    {
        dist[adj.first] = adj.second;
        prev[adj.first] = s_vertex;
    }
    map<int, int> incoming[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++) // incomming
    {
        for (auto it : graph->getAdjacentEdges(i))
        {
            incoming[it.first].insert({i, it.second});
        }
    }

    for (int k = 2; k <= graph->getSize() - 1; k++) // 엣지 개수 증가
    {
        for (int v = 0; v < graph->getSize(); v++) // 모든 버택스 순회
        {
            if (v == s_vertex || incoming[v].empty())
                continue;
            for (int w = 0; w < graph->getSize(); w++)
            {
                if (w == v)
                    continue;
                for (auto it : graph->getAdjacentEdges(w))
                {
                    if (it.first == v)
                    {
                        if (dist[v] > dist[w] + graph->getAdjacentEdges(w).find(v)->second)
                        {
                            dist[v] = dist[w] + graph->getAdjacentEdges(w).find(v)->second;
                            prev[v] = w;
                            if (dist[v] < 0)
                                return false;
                        }
                    }
                }
                // dist[v] = min(dist[v], dist[w] + graph->getAdjacentEdges(w).find(v)->second);
            }
        }
    }

    stack<int> S;
    int end = e_vertex;
    while (prev[end] != s_vertex)
    {
        S.push(prev[end]);
        end = prev[end];
    }
    *ffff << s_vertex << " -> ";
    while (!S.empty())
    {
        *ffff << S.top() << " -> ";
        S.pop();
    }
    *ffff << e_vertex << '\n';
    *ffff << "cost: " << dist[e_vertex] << "\n";
    return true;
}

bool FLOYD(Graph *graph)
{
    int A[graph->getSize()][graph->getSize()];

    for (int i = 0; i < graph->getSize(); i++)
    {
        for (int j = 0; j < graph->getSize(); j++)
        {
            if (i == j)
                A[i][j] = 0;
            else
                A[i][j] = 21474836;
        }
    }

    for (int i = 0; i < graph->getSize(); i++)
    {
        for (auto it : graph->getAdjacentEdges(i))
        {
            A[i][it.first] = it.second;
        }
    }

    for (int k = 0; k < graph->getSize(); k++)
    {
        for (int i = 0; i < graph->getSize(); i++)
        {
            for (int j = 0; j < graph->getSize(); j++)
            {
                if (i == j || j == k || i == k || A[i][j] == A[i][k] + A[k][j])
                    continue;
                A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
                if (A[i][j] < 0) //에러처리
                    return false;
            }
        }
    }

    for (int i = 0; i < graph->getSize(); i++)
    {
        if (i == 0)
        {
            *ffff << "   ";
            for (int k = 0; k <= 6; k++)
                *ffff << "[" << k << "]"
                      << " ";
            *ffff << "\n";
        }
        for (int j = 0; j < graph->getSize(); j++)
        {
            if (j == 0)
                *ffff << "[" << i << "]"
                      << " ";
            if (A[i][j] == 21474836)
                *ffff << 'x' << "   ";
            else
                *ffff << A[i][j] << "   ";
        }
        *ffff << "\n";
    }
    return true;
}