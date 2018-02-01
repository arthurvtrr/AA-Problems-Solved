#include <bits/stdc++.h>

using namespace std;

int n, m, x, y, ans;
vector < int > graph[50050];
set < int > app[50050];
bool visited[50050];

void dfs(int u) {
    visited[u] = true;
    int aux = 1;
    while (app[u].count(aux)) aux++;
    ans = max(ans, aux);

    for (int v : graph[u])
        app[v].insert(aux);
    for (int v : graph[u])
        if (!visited[v])
            dfs(v);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    ans = 0;
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            dfs(i);

    printf("%d\n", ans);
    return 0;
}
