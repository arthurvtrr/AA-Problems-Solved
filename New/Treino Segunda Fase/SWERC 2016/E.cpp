#include <bits/stdc++.h>

using namespace std;

#define N 1010
#define ALP_SIZ 300

struct Automaton {
    int nodes, fail[N], wid[N], endLink[N], child[N][ALP_SIZ];
    queue < int > q;
    bool leaf[N];

    int newnode() {
        fail[nodes] = wid[nodes] = endLink[nodes] = leaf[nodes] = 0;
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
            int c = s[i];
            if (!child[atual][c])
                child[atual][c] = newnode();
            atual = child[atual][c];
        }
        leaf[atual] = true;
        wid[atual] = id;
    }

    void getFails() {
        for (int i = 0; i < ALP_SIZ; i++)
            if (child[0][i]) {
                fail[child[0][i]] = 0, q.push(child[0][i]);
                if (leaf[child[0][i]]) endLink[child[0][i]] = child[0][i];
            }

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int i = 0; i < ALP_SIZ; i++) {
                int v = child[u][i];
                if (!v) { child[u][i] = child[fail[u]][i]; continue; }

                q.push(v);
                int j = fail[u];
                while (j && !child[j][i]) j = fail[j];
                fail[v] = child[j][i];

                if (leaf[v]) endLink[v] = v;
                else endLink[v] = endLink[fail[v]];
            }
        }
    }
} AC;

#define MOD 1000003
#define ll long long

int a, b, n, lim;
ll dp[25][N][8];
string pat[N];
vector < int > nxt[300];

ll solve(int ind, int state, int m) {
    if (dp[ind][state][m] != -1) return dp[ind][state][m];
    if (ind == lim) return m == 7;

    ll ret = 0;
    for (int i = 0; i < 300; i++) {
        if (nxt[i].empty()) continue;

        bool valid = true;

        int atual = state;

        while (atual != 0) {
            bool found = false;

            for (int j : nxt[i])
                if (AC.child[atual][j])
                    found = true;

            if (found) break;

            atual = AC.fail[atual];
        }

        for (int j : nxt[i])
            if (AC.child[atual][j])
                atual = AC.child[atual][j];

        if (AC.endLink[atual] != 0)
            valid = false;

        if (valid) {
            int nxtm = m;
            if (i >= 'a' && i <= 'z') nxtm |= 1;
            if (i >= 'A' && i <= 'Z') nxtm |= 2;
            if (i >= '0' && i <= '9') nxtm |= 4;
            ret += solve(ind+1, atual, nxtm);
            ret %= MOD;
        }
    }

    return dp[ind][state][m] = ret;
}

int main() {
    AC.clear();

    scanf("%d %d", &a, &b);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> pat[i];
        AC.insert(pat[i], i);
    }
    AC.getFails();

    for (char c = 'a'; c <= 'z'; c++) {
        nxt[c].push_back(c);
        nxt[c].push_back(toupper(c));
        nxt[toupper(c)].push_back(toupper(c));
        nxt[toupper(c)].push_back(c);
    }

    for (char c = '0'; c <= '9'; c++)
        nxt[c].push_back(c);

    nxt['0'].push_back('o'); nxt['o'].push_back('0');
    nxt['0'].push_back('O'); nxt['O'].push_back('0');
    nxt['1'].push_back('i'); nxt['i'].push_back('1');
    nxt['1'].push_back('I'); nxt['I'].push_back('1');
    nxt['3'].push_back('e'); nxt['e'].push_back('3');
    nxt['3'].push_back('E'); nxt['E'].push_back('3');
    nxt['5'].push_back('s'); nxt['s'].push_back('5');
    nxt['5'].push_back('S'); nxt['S'].push_back('5');
    nxt['7'].push_back('t'); nxt['t'].push_back('7');
    nxt['7'].push_back('T'); nxt['T'].push_back('7');

    ll ans = 0;
    for (int i = a; i <= b; i++) {
        lim = i;
        memset(dp, -1, sizeof dp);
        ans += solve(0, 0, 0);
        ans %= MOD;
    }

    printf("%lld\n", ans);
    return 0;
}
