T = 0;
while ((T contains less than n - 1 edges) && (E not empty))
{
    choose an edge(v, w) from E of lowest cost;
    delete (v, w)from E;
    if ((v, w)does not create a cycle in T)
        add(v, w) to T;
    else
        discard(v, w);
}
if (T contains fewer than n - 1 edges)
cout << "no spanning tree;"