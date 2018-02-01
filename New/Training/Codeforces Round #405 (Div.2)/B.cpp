#include <bits/stdc++.h>

using namespace std;

int n, m, x, y;
vector < int > graph[150500], comp;
bool visited[150500];

void dfs(int u) {
    visited[u] = true;
    comp.push_back(u);

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

    bool possible = true;

    for (int i = 1; i <= n; i++)
        if (!visited[i]) {
            comp.clear();
            dfs(i);
            for (int v : comp)
                if (graph[v].size() != (int)comp.size() - 1)
                    possible = false;
        }

    if (possible) printf("YES\n");
    else printf("NO\n");

    return 0;
}

