#include <bits/stdc++.h>
#include "ListGraph.h"
#include "GraphMethod.h"

#define BIGBIG_NUM 214748364
using namespace std;

typedef pair<int, int> iPair;

int dfs_cnt = 1;

void insertion(tuple<int, int, int> &e, vector<tuple<int, int, int>> &a, int i)
{
    while (i > -1 && e < a[i]) // Insertion sort using sentinel
    {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}

void insertion_sort(vector<tuple<int, int, int>> &a, const int low, const int high)
{
    for (int j = low; j <= high; j++) // Check Every Element
    {
        tuple<int, int, int> temp = a[j];
        insertion(temp, a, j - 1);
    }
}

void quick_sort(vector<tuple<int, int, int>> &a, const int left, const int right)
{
    if (left < right)
    {

        if (right - left + 1 <= 6)
            insertion_sort(a, left, right); // if segment size is lower than 7 Do insertion sort
        else
        {
            int i = left;
            int j = right + 1;
            tuple<int, int, int> pivot = a[left];
            do // Compare using pivot
            {
                do
                    i++;
                while (a[i] < pivot);
                do
                    j--;
                while (a[j] > pivot);
                if (i < j)
                    swap(a[i], a[j]);
            } while (i < j);
            swap(a[left], a[j]);

            quick_sort(a, left, j - 1);  // divide
            quick_sort(a, j + 1, right); // divide
        }
    }
}

int find_par_vertex(int *&par_vertex, int x) // find parent vertex
{
    if (par_vertex[x] == x)
        return x;
    else
        return par_vertex[x] = find_par_vertex(par_vertex, par_vertex[x]);
}

void union_par_vertex(int *&par_vertex, int x, int y) // union parent vertex
{
    x = find_par_vertex(par_vertex, x);
    y = find_par_vertex(par_vertex, y);
    if (x < y)
        par_vertex[y] = x;
    else
        par_vertex[x] = y;
}

bool BFS(Graph *graph, int vertex, ofstream &fout)
{
    int cnt = 1;
    int vis[graph->getSize() + 2] = {0}; // Check for vertex already visited

    queue<int> Q;
    Q.push(vertex);

    vis[vertex] = 1;
    fout << "startvertex: " << vertex << "\n"
         << vertex << " -> ";
    while (!Q.empty()) // Start BFS
    {
        auto cur = Q.front();
        Q.pop();
        for (auto edge : graph->getAdjacentEdges(cur)) // Searching Adjacent vertex
        {
            if (vis[edge.first]) // Already vistied
                continue;
            vis[edge.first] = 1; // Newly visit
            Q.push(edge.first);

            fout << edge.first;
            if (++cnt < graph->getSize())
                fout << " -> ";
        }
    }
    fout << "\n";
    return true;
}

bool DFS(Graph *graph, int vertex, ofstream &fout)
{
    int cnt = 0;
    int graph_size = graph->getSize();
    int vis[graph_size + 2] = {0}; // Check for vertex already visited

    stack<int> S;
    S.push(vertex);

    vis[vertex] = 1;
    fout << "startvertex: " << vertex << "\n";
    while (!S.empty()) // Start DFS
    {
        auto cur = S.top();
        S.pop(); // A visiting vertex
        fout << cur;
        if (++cnt < graph_size)
            fout << " -> ";
        for (auto edges : graph->getAdjacentEdges(cur)) // Searching Adjacent vertex
        {
            if (vis[edges.first])
                continue;
            vis[edges.first] = 1;
            S.push(edges.first);
        }
    }
    fout << "\n";
    return true;
}

bool DFS_R(Graph *graph, vector<bool> *visit, int vertex, ofstream &fout)
{
    visit[0][vertex] = true;
    fout << vertex;
    if (++dfs_cnt < graph->getSize())
        fout << " -> ";
    else // When visit all the vertex,
        fout << "\n";
    for (auto edges : graph->getAdjacentEdges(vertex)) // Searching Adjacent vertex
    {
        if (!visit[0][edges.first])
            DFS_R(graph, visit, edges.first, fout); // Increasing depth
    }
}

bool Kruskal(Graph *graph, ofstream &fout)
{
    int sum = 0;
    int graph_size = graph->getSize();
    int *parent = new int[graph_size];
    map<int, int> MST[graph_size];      // Minnium Spanning Tree
    vector<tuple<int, int, int>> edges; // The relationship between all vertex and edge

    for (int i = 0; i < graph_size; i++)
    {
        for (auto edge : graph->getAdjacentEdges(i))
        {
            tuple<int, int, int> tmp = make_tuple(edge.second, i, edge.first); // Make min Heap
            edges.push_back(tmp);
        }
    }
    for (int i = 0; i < graph_size; i++)
        parent[i] = i;

    quick_sort(edges, 0, edges.size() - 1); // sorting edges

    for (int i = 0; i < graph_size && !edges.empty(); i++) // Making MST
    {
        tuple<int, int, int> cur = edges.front();
        edges.erase(edges.begin());
        if (find_par_vertex(parent, get<1>(cur)) != find_par_vertex(parent, get<2>(cur))) // Check if a cycle is formed
        {
            union_par_vertex(parent, get<1>(cur), get<2>(cur));
            MST[get<1>(cur)].insert({get<2>(cur), get<0>(cur)});
            MST[get<2>(cur)].insert({get<1>(cur), get<0>(cur)});
            sum += get<0>(cur);
        }
    }
    for (int i = 0; i < graph_size; i++)
    {
        fout << "[" << i << "] ";
        for (auto cur : MST[i])
            fout << cur.first << "(" << cur.second << ") ";
        fout << "\n";
    }
    fout << "cost: " << sum << "\n";
    if (sum < 0) // If MST cannot be created
        return false;
    return true;
}

bool Dijkstra(Graph *graph, int vertex, ofstream &fout)
{
    int graph_size = graph->getSize();
    int prev[graph_size];

    vector<int> dist(graph_size, BIGBIG_NUM);
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    dist[vertex] = 0;
    pq.push(make_pair(0, vertex));
    fout << "startvertex: " << vertex << "\n";

    for (int i = 0; i < graph_size; i++) // Show past paths
        prev[i] = i;
    while (!pq.empty()) // Start Dijkstra
    {
        int via_vertex = pq.top().second; // via vertex
        pq.pop();

        for (auto edge : graph->getAdjacentEdges(via_vertex)) // Check adjacent vertex
        {
            int dest_vertex = edge.first;
            int weight_vertex = edge.second;

            if (dist[dest_vertex] > dist[via_vertex] + weight_vertex) // If it's faster to go straight than a layover,
            {
                dist[dest_vertex] = dist[via_vertex] + weight_vertex;
                pq.push(make_pair(dist[dest_vertex], dest_vertex));
                prev[dest_vertex] = via_vertex;
            }
        }
    }
    for (int i = 0; i < graph_size; i++) // Print the past path
    {
        if (i == vertex)
            continue;
        fout << "[" << i << "] ";
        int cur_vertex = i;
        if (prev[cur_vertex] != cur_vertex)
        {
            stack<int> S;
            while (prev[i] != vertex)
            {
                S.push(prev[i]);
                i = prev[i];
            }
            fout << vertex << " -> ";
            while (!S.empty())
            {
                fout << S.top() << " -> ";
                S.pop();
            }
            fout << cur_vertex << " (" << dist[cur_vertex] << ")"
                 << "\n";
        }
        else
            fout << "x"
                 << "\n";
        i = cur_vertex;
    }
    return true;
}

bool Bellmanford(Graph *graph, int s_vertex, int e_vertex, ofstream &fout)
{
    stack<int> S;
    int end_vertex;
    int graph_size = graph->getSize();
    int prev[graph_size];
    int dist[graph_size];

    map<int, int> lead_up_vertex[graph_size]; // the vertexes leading up to the present vertex
    for (int i = 0; i < graph_size; i++)
    {
        prev[i] = i;
        dist[i] = BIGBIG_NUM;
    }
    dist[s_vertex] = 0; // The number of edges 0

    for (auto edge : graph->getAdjacentEdges(s_vertex)) // The numer of s_vertex's adjancent edge
    {
        dist[edge.first] = edge.second;
        prev[edge.first] = s_vertex;
    }
    for (int i = 0; i < graph_size; i++) // Find leading up vertices
    {
        for (auto edge : graph->getAdjacentEdges(i))
            lead_up_vertex[edge.first].insert({i, edge.second});
    }

    for (int k = 2; k <= graph_size - 1; k++) // Number of available edges
    {
        for (int v = 0; v < graph_size; v++) // Check shortest distance for all vertices
        {
            if (lead_up_vertex[v].empty() || v == s_vertex)
                continue;
            for (int w = 0; w < graph_size; w++) // A direct comparison between diesel and non-stop
            {
                if (w == v)
                    continue;
                for (auto edge : graph->getAdjacentEdges(w))
                {
                    if (v == edge.first)
                    {
                        if (dist[v] > dist[w] + graph->getAdjacentEdges(w).find(v)->second)
                        {
                            prev[v] = w;
                            dist[v] = dist[w] + graph->getAdjacentEdges(w).find(v)->second;
                            if (dist[v] < 0) // The negative number cycle generates
                                return false;
                        }
                    }
                }
            }
        }
    }

    end_vertex = e_vertex;
    while (prev[end_vertex] != s_vertex) // Print Shortest distance path from start to finish
    {
        S.push(prev[end_vertex]);
        end_vertex = prev[end_vertex];
    }
    fout << s_vertex << " -> ";
    while (!S.empty())
    {
        fout << S.top() << " -> ";
        S.pop();
    }
    fout << e_vertex << "\n"
         << "cost: " << dist[e_vertex] << "\n";
    return true;
}

bool FLOYD(Graph *graph, ofstream &fout)
{
    int graph_size = graph->getSize();
    int dist_board[graph_size][graph_size];

    for (int i = 0; i < graph_size; i++) // Initialize distance board 1
    {
        for (int j = 0; j < graph_size; j++)
        {
            if (i == j)
                dist_board[i][j] = 0;
            else
                dist_board[i][j] = BIGBIG_NUM;
        }
    }

    for (int i = 0; i < graph_size; i++) // Initialize distance board 2
    {
        for (auto edge : graph->getAdjacentEdges(i))
            dist_board[i][edge.first] = edge.second;
    }

    for (int k = 0; k < graph_size; k++) // As the edge increases, the minimum distance is found again.
    {
        for (int i = 0; i < graph_size; i++)
        {
            for (int j = 0; j < graph_size; j++)
            {
                if (i == j || j == k || i == k || dist_board[i][j] == dist_board[i][k] + dist_board[k][j])
                    continue;
                dist_board[i][j] = min(dist_board[i][j], dist_board[i][k] + dist_board[k][j]); // Find smallest distance
                if (dist_board[i][j] < 0)                                                      // The negative number cycle generates
                    return false;
            }
        }
    }

    for (int i = 0; i < graph_size; i++) // Print distance board
    {
        if (i == 0)
        {
            fout << "     ";
            for (int k = 0; k < graph_size; k++)
                fout << "[" << k << "]\t";
            fout << "\n";
        }
        for (int j = 0; j < graph_size; j++)
        {
            if (j == 0)
                fout << "[" << i << "]\t";
            if (dist_board[i][j] == BIGBIG_NUM)
                fout << 'x' << "\t";
            else
                fout << dist_board[i][j] << "\t";
        }
        fout << "\n";
    }
    return true;
}