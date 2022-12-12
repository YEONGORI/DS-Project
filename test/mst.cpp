E0.K = -MAXKEY;
for (p = root; p != NULL; p = Ai)
{
    Let p have the format n, A0, (E1, A1), ..., (En, An);
    En + 1.K = MAXKEY;
    Determine i such that Ei.K <= x < Ei + 1.K;
    if (x == Ei.K)
        return Ei;
}
return NULL;