if Tree contains a single path P then
    for each combination(denoted as B) of the nodes in the path P
        generate pattern B U A with support_count = minimum support count of nodes in B;
else
    for each
        ai int the header of Tree
        {
            generate patternB = ai U A with support_count = ai.support_count;
            construct B 's conditional pattern base and then B' s conditional FP_tree TreeB;
            if (TreeB != 0)
                then call FP_growth(TreeB, B);
        }