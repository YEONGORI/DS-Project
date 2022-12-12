#include <bits/stdc++.h>

using namespace std;

Y = {0};
for (T = 0; T contains fewer than n - 1 edges; add(u, v) to T)
{
    Let(u, v) be a least-cost edge such that u ( Y and v !( Y;
    if (there is no such edge)
        break;
    add v to Y;
}
if (T contains fewer than n - 1 edges)
    cout << "no spanning tree"

        void
        prim(int n, const number Wp[][], set_of_edges &F)
    {
        index i, vnear;
        number min;
        edge e;
        index nearest[2..n];
        number distance[2..n];

        F = 0;
        for (i = 2; i <= n; i++)
        {
            nearest[i] = 1;
            distance[i] = W[1][i];
        }

        repeat(n - 1 times)
        {
            for (i = 2; i <= n; i++)
            {
                if (0 <= distance[i] < min)
                {
                    min = distance[i];
                    vnear = i;
                }
            }

            e = edge connecting vertices indexed by vnear and nearest[vnear];
            add e to F;
            distance[vnear] = -1;
            for (i = 2; i <= n; i++)
            {
                if (W[i][near] < distnace[i])
                {
                    distance[i] = W[i][vnear];
                    nearest[i] = vnear;
                }
            }
        }
    }