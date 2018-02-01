#include <bits/stdc++.h>

using namespace std;

int q, x, y, z;

#define ALP_SIZ 3

struct TrieNode {
    int quant = 0;
    TrieNode *child[ALP_SIZ];

    TrieNode() {
        for (int i = 0; i < ALP_SIZ; i++)
            child[i] = NULL;
    }
};

void change(TrieNode *root, int v, int c) {
    TrieNode *aux = root;

    for (int i = 29; i >= 0; i--) {
        int x = (v & (1 << i)) > 0;
        if (!aux->child[x])
            aux->child[x] = new TrieNode();

        aux = aux->child[x];
        aux->quant += c;
    }
}

int dfs(TrieNode *root, int p, int l, int lvl) {
    if (lvl == -1) return 0;
    if (!root->child[0]) root->child[0] = new TrieNode();
    if (!root->child[1]) root->child[1] = new TrieNode();

    int ret = 0;
    if (l & (1 << lvl)) {
        if (p & (1 << lvl)) ret += root->child[1]->quant + dfs(root->child[0], p, l, lvl-1);
        else ret += root->child[0]->quant + dfs(root->child[1], p, l, lvl-1);
    }
    else {
        if (p & (1 << lvl)) ret += dfs(root->child[1], p, l, lvl-1);
        else ret += dfs(root->child[0], p, l, lvl-1);
    }
    return ret;
}

int main() {
    TrieNode *root = new TrieNode();

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &x, &y);

        if (x == 1) change(root, y, 1);
        else if (x == 2) change(root, y, -1);
        else {
            scanf("%d", &z);
            printf("%d\n", dfs(root, y, z, 29));
        }
    }

    return 0;
}

