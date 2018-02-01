#include <bits/stdc++.h>

using namespace std;

#define N 110
#define ALP_SIZ 26

struct Automaton {
    int nodes, fail[N], mask[N];
    int child[N][ALP_SIZ];
    queue < int > q;

    int newnode() {
        mask[nodes] = 0;
        memset(child[nodes], 0, sizeof(child[nodes]));
        return nodes++;
    }

    void clear() {
        nodes = 0;
        newnode();
    }

    void insert(string s, int id) {
        int atual = 0;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (!child[atual][c])
                child[atual][c] = newnode();
            atual = child[atual][c];
        }
        mask[atual] |= 1 << id;
    }

    void getFails() {
        for (int i = 0; i < ALP_SIZ; i++)
            if (child[0][i])
                fail[child[0][i]] = 0, q.push(child[0][i]);

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int i = 0; i < ALP_SIZ; i++) {
                int v = child[u][i];
                if (!v) { child[u][i] = child[fail[u]][i]; continue; }

                q.push(v);
                int j = fail[u];
                while (j && !child[j][i]) j = fail[j];
                fail[v] = child[j][i], mask[v] |= mask[fail[v]];
            }
        }
    }
} AC;


