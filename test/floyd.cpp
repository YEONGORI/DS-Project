#include <bits/stdc++.h>
using namespace std;

int test(int n)
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                A[i][j][k] = min(A[i][j][k - 1], A[i][j][k - 1] A[k][j][j - 1]);
            }
        }
    }
}

int test2(int n)
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
            }
        }
    }
}