if the
    tree is empty return NULL
        K0 = -MAXKEY for (p = root; p is an index node; p = Ai)
    {
        Let p have the format n, A0, (K1, A1), ..., (Kn, An);
        Kn + 1 = MAXKEY;
        Determine i such that Ki <= x < Ki + 1;
    }
Search p for an element E with key x;
if such
    and element is found return E else return NULL;