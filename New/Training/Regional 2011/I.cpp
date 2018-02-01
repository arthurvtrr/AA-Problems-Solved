#include <bits/stdc++.h>

using namespace std;

int n, m, x, y, p;
vector < int > graph[2200], comp[2200], aux;

int counter, scc, dfs_num[2200], dfs_low[2200];
bool visited[2200];

void dfs(int u) {
    dfs_low[u] = dfs_num[u] = counter++;
    aux.push_back(u);
    visited[u] = true;

    for (int v : graph[u]) {
        if (!dfs_num[v])
            dfs(v);
        if (visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {
        while (1) {
            int v = aux.back();
            aux.pop_back();
            visited[v] = false;
            comp[scc].push_back(v);

            if (u == v) break;
        }
        scc++;
    }
}

int main() {
    while (1) {
        scanf("%d %d", &n, &m);
        if (n + m == 0) break;

        for (int i = 0; i < 2200; i++) {
            graph[i].clear();
            comp[i].clear();
            visited[i] = dfs_num[i] = dfs_low[i] = 0;
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &p);
            graph[x].push_back(y);
            if (p == 2) graph[y].push_back(x);
        }

        counter = scc = 1;
        for (int i = 1; i <= n; i++)
            if (!dfs_num[i])
                dfs(i);

        printf("%d\n", scc == 2);
    }

    return 0;
}
