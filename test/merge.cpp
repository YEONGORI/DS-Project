template <class T>
void Merge(T *initList, T *mergedList, const int l, const int m, const int n)
{
    for (int i1 = 1, iResult = 1, i2 = m + 1; i1 <= m && i2 <= n; iResult++)
    {
        if (initList[i1] <= initList[i2])
        {
            mergedList[iResult] = initList[i1];
            i1++;
        }
        else
        {
            mergedList[iResult] = initList[i2];
            i2++;
        }
        copy(initList + i1, initList + m + 1, mergedList + iResult);
        copy(initList + i2, initList + n + 1, mergedList + iResult);
    }
}

template <class T>
void MergePass(T *initList, T *resultList, const int n, const int s)
{
    for (int i = 1; i <= n - 2 * s + 1; i += 2 * s)
        Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);
    if ((i + s - 1) < n)
        Merge(initList, resultList, i, i + s - 1, n);
    else
        copy(initList + i, initList + n + 1, resultList + i);
}

template <class T>
void MergeSort(T *a, const int n)
{
    T *tempList = new T[n + 1];
    for (int i = 1; i < n; i *= 2)
    {
        MergePass(a, tempList, n, i);
        i *= 2;
        MergePass(tempList, a, n, i);
    }
    delete[] tempList;
}
