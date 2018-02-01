#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >
#define INF 1000000000

int n, m, c, k;
vector < pii > graph[300];
int dist[300], path[300];

void solve() {
    for (int i = 0; i < 300; i++)
        dist[i] = INF;

    priority_queue < pii > fila;
    fila.push(pii(0, k));
    dist[k] = 0;

    int ans = INF;

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();

        for (pii v : graph[u]) {
            if (v.first < c) ans = min(ans, dist[u] + v.second + path[v.first]);
            else if (dist[v.first] > dist[u] + v.second) {
                dist[v.first] = dist[u] + v.second;
                fila.push(pii(-dist[v.first], v.first));
            }
        }
    }

    printf("%d\n", ans);
}

int main() {
    while (1) {
        scanf("%d %d %d %d", &n, &m, &c, &k);
        if (n + m + c + k == 0) break;

        for (int i = 0; i < 300; i++) {
            graph[i].clear();
            path[i] = 0;
        }

        for (int i = 0; i < m; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            graph[x].push_back(pii(y, z));
            graph[y].push_back(pii(x, z));
        }

        int d = 0;
        for (int i = c-2; i >= 0; i--) {
            int aux = 0;
            for (int j = 0; j < graph[i].size(); j++)
                if (graph[i][j].first == i+1) {
                    aux = graph[i][j].second;
                    break;
                }

            d += aux;
            path[i] = d;
        }

        solve();
    }
    return 0;
}
