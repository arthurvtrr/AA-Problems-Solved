#include <bits/stdc++.h>

using namespace std;

int n, m;
string pat[110], w[110];

struct Node {
    bool leaf;
    Node *child[300];
    Node() {
        leaf = false;
        for (int i = 0; i < 300; i++)
            child[i] = NULL;
    }
};

Node *root;

void insertWord(string s) {
    Node *aux = root;
    for (int i = 0; i < s.size(); i++) {
        if (!aux->child[s[i]])
            aux->child[s[i]] = new Node();
        aux = aux->child[s[i]];
    }
    aux->leaf = true;
}

int dp[88], atual;

int solve(int ind) {
    if (dp[ind] != -1) return dp[ind];
    if (ind == w[atual].size()) return 0;

    int ret = 1000000, pos = 100;

    for (int j = ind; j < w[atual].size(); j++) {
        Node *aux = root;
        for (int i = j; i < min((int)w[atual].size(), j+15); i++) {
            if (!aux->child[w[atual][i]]) break;
            aux = aux->child[w[atual][i]];
            if (aux->leaf) {
                pos = min(pos, i);
                break;
            }
        }
    }

    if (pos == 100) ret = solve(ind+1);
    else {
        for (int i = ind; i <= pos; i++)
            ret = min(ret, 1 + solve(i+1));
    }

    return dp[ind] = ret;
}

int main() {
    while (1) {
        scanf("%d %d", &n, &m);
        getchar();
        if (n + m == 0) break;

        root = new Node();

        for (int i = 0; i < n; i++) {
            getline(cin, pat[i]);
            insertWord(pat[i]);
        }

        int ans = 0;
        for (int i = 0; i < m; i++) {
            getline(cin, w[i]);
            w[i] += " ";
            atual = i;
            memset(dp, -1, sizeof dp);
            ans += solve(0);
        }
        printf("%d\n", ans);
    }

    return 0;
}
