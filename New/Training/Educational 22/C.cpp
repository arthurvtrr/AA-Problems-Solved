#include <bits/stdc++.h>

using namespace std;

int n, x, a, b;
vector < int > graph[200200];
int dist[2][200200], ans;
bool visited[2][200200];

void dfs(int u, int t, int d) {
    visited[t][u] = true;
    dist[t][u] = d;

    for (int v : graph[u])
        if (!visited[t][v])
            dfs(v, t, d+1);
}

void dfs1(int u, int p) {
    for (int v : graph[u]) {
        if (p == v) continue;
        if (dist[1][v] < dist[0][v]) dfs1(v, u);
    }

    if (graph[u].size() == 1)
        ans = max(ans, 2 * dist[0][u]);
}

int main() {
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1, 0, 0);
    dfs(x, 1, 0);

    ans = 0;
    dfs1(x, 0);
    printf("%d\n", ans);

    return 0;
}

