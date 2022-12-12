#include <bits/stdc++.h>
using namespace std;

template <class T>
void insertionSort(T *a, const int n)
{
    for (int j = 2; j < n; j++)
        T temp = a[j];
    insert(temp, a, j - 1);
}

template <class T>
void insert(const T &e, T *a, int i)
{
    a[0] = e;
    while (e < a[i])
    {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}

template <class T>
void quickSort(T *a, const int left, const int right)
{
    if (left < right)
    {
        int i = left,
            j = right + 1,
            pivot = a[left];
        do
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

        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}