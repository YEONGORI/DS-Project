#include <bits/stdc++.h>
using namespace std;

template <class K, class E>
pair<K, E> *Chaining<K, E>::Get(const K &k)
{
    int i = h(k);
    for (ChainNode<pair<K, E>> *current = ht[i]; current; current = current->link)
        if (current->data.first == k)
            return &current->data;
    return NULL;
}

int main()
{
    unordered_map<string, string> u = {
        {"RED", "#FF0000"},
        {"GREEN", "#00FF00"},
        {"BLUE", "#0000FF"}};

    for (const auto &n : u)
    {
        cout << "Key::[" << n.first << "] Value: [" << n.second << "]\n";
    }

    u["BLACK"] = "#000000";
    u["WHITE"] = "#FFFFFF";

    cout << "The HEX of color RED is: [" << u["RED"] << "]\n";
    cout << "The HEX of color BLACK is";
}