#include <bits/stdc++.h>

using namespace std;

void MatrixWDiagraph::BellmanFord(const int n, const int s)
{
    for (int i = 0; i < n; i++)
        dist[i] = length[s][i];
    for (int k = 2; k <= n - 1; k++)
        for (each v such that v != s && v has at least one incomming edges)
            for (each<w, v> in the graph)
                dist[v] = min(dist[v], dist[w] + length[w][v])
}