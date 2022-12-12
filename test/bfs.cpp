#include <bits/stdc++.h>

using namespace std;

virtual void Graph::BFS(int v)
{
    visited = new bool[n];
    fill(visited, visited + n, false);
    visited[v] = true;
    Queue<int> q;
    q.Push(v);
    while (!q.Empty())
    {
        v = q.front();
        q.Pop();
        for (all vertices w adjacent v)
        {
            if (!visited[w])
            {
                q.Push(w);
                visited[w] = true;
            }
        }
    }
    delete[] visited
}