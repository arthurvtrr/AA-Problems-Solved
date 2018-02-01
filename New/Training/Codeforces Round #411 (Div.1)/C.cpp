#include <bits/stdc++.h>

using namespace std;

int n, m, x, y, color[300300];
bool used[300300], visited[300300];
vector < int > graph[300300], ice[300300], group, ok;

void dfs(int u) {
    visited[u] = true;
    group.clear(); ok.clear();

    if (ice[u].size() > 1) {
        for (int i = 0; i < ice[u].size(); i++)
            if (color[ice[u][i]] == 0) group.push_back(ice[u][i]);
            else ok.push_back(ice[u][i]);

        for (int j = 0; j < ok.size(); j++)
            used[color[ok[j]]] = true;

        int newc = 1;
        for (int j = 0; j < group.size(); j++) {
            while (used[newc]) newc++;
            color[group[j]] = newc++;
        }

        for (int j = 0; j < ok.size(); j++)
            used[color[ok[j]]] = false;
    }

    for (int v : graph[u])
        if (!visited[v])
            dfs(v);
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);

        for (int j = 0; j < x; j++) {
            scanf("%d", &y);
            ice[i+1].push_back(y);
        }
    }

    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1);

    int colors = 1;
    for (int i = 1; i <= m; i++)
        colors = max(colors, color[i]);

    printf("%d\n", colors);
    for (int i = 1; i <= m; i++) {
        if (i > 1) printf(" ");
        printf("%d", max(1, color[i]));
    }
    printf("\n");

    return 0;
}
