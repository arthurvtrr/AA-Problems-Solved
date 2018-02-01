#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define N 5050
#define ll long long

int t, n, m, a, b, msk[N], atual;
vector < int > graph[N], aux;
ll quant[1030], ans[11], dp[N];
bool visited[N];

void dfs(int u) {
    visited[u] = true;
    dp[u] = 1;
    aux.push_back(u);
    for (int v : graph[u])
        if (!visited[v] && (msk[v] & atual) == atual) {
            dfs(v);
            dp[u] *= dp[v] + 1;
            dp[u] %= MOD;
        }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < N; i++) {
            msk[i] = 0;
            graph[i].clear();
        }

        scanf("%d %d", &n, &m);
        for (int i = 0; i < n-1; i++) {
            scanf("%d %d", &a, &b);
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        for (int i = 1; i <= n; i++)
            for (int j = 0; j < m; j++) {
                scanf("%d", &a);
                msk[i] |= a << j;
            }

        memset(ans, 0, sizeof ans);
        memset(quant, 0, sizeof quant);

        for (int i = (1 << m) - 1; i >= 0; i--) {
            atual = i;
            memset(visited, 0, sizeof visited);
            for (int j = 1; j <= n; j++)
                if (!visited[j] && (msk[j] & i) == i) {
                    dfs(j);

                    for (int v : aux) {
                        quant[i] += dp[v];
                        quant[i] %= MOD;
                    }

                    aux.clear();
                }

            for (int j = i+1; j < 1 << m; j++)
                if ((j & i) == i) {
                    quant[i] -= quant[j];
                    quant[i] += MOD;
                    quant[i] %= MOD;
                }
        }

        for (int i = 0; i < 1 << m; i++) {
            ans[__builtin_popcount(i)] += quant[i];
            ans[__builtin_popcount(i)] %= MOD;
        }

        for (int i = 0; i <= m; i++) {
            if (i) printf(" ");
            printf("%lld", ans[i]);
        }
        printf("\n");
    }

    return 0;
}
