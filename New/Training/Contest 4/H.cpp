#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, m, r, e, x, y;
vector < int > graph[1010], comp;
set < pii > edges;
bool visited[1010];

void dfs(int u) {
    visited[u] = true;
    comp.push_back(u);

    for (int v : graph[u]) {
        edges.insert(pii(min(u, v), max(u, v)));
        if (!visited[v])
            dfs(v);
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &r, &e);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            comp.clear();
            edges.clear();
            dfs(i);

            if (comp.size() > 2) {
                int siz = comp.size();
                ans += min(r * (siz * (siz-1) / 2 - (int)edges.size()), e * siz);
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}

