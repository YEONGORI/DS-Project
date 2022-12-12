void MatrixWDigraph::ShortestPath(const int n, const int v)
{
    for (int i = 0; i < n; i++)
    {
        s[i] = false;
        dist[i] = length[v][i];
    }

    s[v] = true;
    dist[v] = 0;

    for (i = 0; i < n - 2; i++)
    {
        int u = Choose(n);
        s[u] = true;

        for (int w = 0; w < n; w++)
        {
            if (a[w] == false)
                dist[w] = min(dist[u] + length[u][w], dist[w]);
        }
    }
}