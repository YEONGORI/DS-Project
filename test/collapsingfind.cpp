int Sets::CollapsingFind(int i)
{
    for (int r = i; parent[r] >= 0; r = parent[r])
        ;
    while (i != r)
    {
        int s = parent[i];
        parent[i] = r;
        i = s;
    }
}