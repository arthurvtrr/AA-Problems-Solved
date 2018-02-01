#include <bits/stdc++.h>

using namespace std;

int n, m, typ[100100], a, b, id[100100], lvl[100100];
vector < int > graph[100100];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &typ[i]);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        id[a]++;
        graph[b].push_back(a);
    }

    queue < int > fila;
    for (int i = 0; i < n; i++)
        if (id[i] == 0) {
            fila.push(i);
            if (typ[i] == 1) lvl[i] = 1;
        }

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int v : graph[u]) {
            id[v]--;
            lvl[v] = max(lvl[v], lvl[u] + (typ[u] == 0 && typ[v] == 1));
            if (id[v] == 0) fila.push(v);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, lvl[i]);
    printf("%d\n", ans);

    return 0;
}
