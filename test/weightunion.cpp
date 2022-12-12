void Sets::WeightUnion(int i, int j)
{
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j])
    {
        parent[i] = j;
        parent[j] = tmep;
    }
    else
    {
        parent[j] = i;
        parent[i] = temp;
    }
}