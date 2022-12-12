Search the B-tree for and element E with key x.K.
if such and E is found, replace E with x and return;
Otherwise, let p be the leaf into which x is to be inserted
               q = NULL;
for (e = x; p != NULL; p = p->parent())
{
    Insert(e, q) into appropriate position in node p;
    Let the resulting node have the form : n, A0, (E1, A1), ..., (En, An);
    if (n <= m - 1)
    {
        write node p to disk;
        return;
    }
    Let p and q be defined as in Eq.e = E[m / 2];
    write nodes p and q to the disk;
}
Create a new node r with for mat 1, root, (e, q);
root = r;
write root to disk;