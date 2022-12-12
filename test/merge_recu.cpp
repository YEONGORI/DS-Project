template <class T>
int rMergeSort(T *a, int *link, const int left, const int right)
{
    if (left >= right)
        return left;
    int mid = (left + right) / 2;
    return ListMerge(a, link, rMergeSort(a, link, left, mid), rMergeSort(a, link, mid + 1, right));
}

template <class T>
int ListMerge(T *a, int *link, const int start1, const int start2)
{
    int iResult = 0;
    for (int i1 = start1, i2 = start2; i1 && i2;)
    {
        if (a[i1] <= a[i2])
        {
            link[iResult] = il;
            iResult = i1;
            i1 = link[i1];
        }
        else
        {
            link[iResult] = i2;
            iResult = i2;
            i2 = link[i2];
        }

        if (i1 == 0)
            link[iResult] = i2;
        else
            link[iResult] = i1;
        return link[0];
    }
}