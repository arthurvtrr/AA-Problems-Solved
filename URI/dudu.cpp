#include <bits/stdc++.h>

using namespace std;

bool cicle, visited[11000], ancestors[11000];
vector < int > graph[11000];

void dfs(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) {
            ancestors[u] = true;
            dfs(v);
            ancestors[u] = false;
        }
        else if (ancestors[v]) cicle = true;
    }
}

int main() {
    int t, n, m, a, b;
    scanf("%d", &t);

    for (int ct = 0; ct < t; ct++) {
        cicle = false;
        for (int i = 0; i < 11000; i++) {
            visited[i] = false;
            graph[i].clear();
        }

        scanf("%d %d", &n, &m);

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            graph[a].push_back(b);
        }

        for (int i = 1; i <= n; i++)
            if (!visited[i])
                dfs(i);

        if (cicle) printf("SIM\n");
        else printf("NAO\n");
    }

    return 0;
}
