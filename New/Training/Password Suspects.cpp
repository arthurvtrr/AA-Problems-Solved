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

int n, m;
string pats[20];

#define ll long long

ll dp[30][110][1 << 10];
vector < char > aux[30][110][1 << 10];

ll solve(int ind, int node, int mask) {
    if (dp[ind][node][mask] != -1)
        return dp[ind][node][mask];
    if (ind == n)
        return mask == (1 << m) - 1;

    ll ret = 0;
    for (int i = 0; i < 26; i++) {
        ll x = solve(ind+1, AC.child[node][i], mask | AC.mask[AC.child[node][i]]);
        if (x) aux[ind][node][mask].push_back(i + 'a');
        ret += x;
    }
    return dp[ind][node][mask] = ret;
}

void printAll(int ind, int node, int mask, string s) {
    for (char c : aux[ind][node][mask])
        printAll(ind+1, AC.child[node][c - 'a'], mask | AC.mask[AC.child[node][c - 'a']], s + c);
    if (s.size() == n) cout << s << endl;
}

int main() {
    int tc = 1;
    while (1) {
        scanf("%d %d", &n, &m);
        if (n + m == 0) break;

        AC.clear();
        for (int i = 0; i < m; i++) {
            cin >> pats[i];
            AC.insert(pats[i], i);
        }
        AC.getFails();

        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 110; j++)
                for (int k = 0; k < (1 << 10); k++) {
                    dp[i][j][k] = -1;
                    aux[i][j][k].clear();
                }

        ll quant = solve(0, 0, 0);
        printf("Case %d: %lld suspects\n", tc++, quant);
        if (quant <= 42) printAll(0, 0, 0, "");
    }

    return 0;
}
