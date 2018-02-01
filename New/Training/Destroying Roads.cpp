#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000

int n, m, x, y;
int s1, t1, l1, s2, t2, l2;
vector < int > graph[3030];
int dist[3030][3030];

void bfs(int ini) {
    for (int i = 0; i < 3030; i++)
        dist[ini][i] = INF;
    dist[ini][ini] = 0;
    queue < int > fila;
    fila.push(ini);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int v : graph[u])
            if (dist[ini][v] > dist[ini][u] + 1) {
                dist[ini][v] = dist[ini][u] + 1;
                fila.push(v);
            }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    scanf("%d %d %d", &s1, &t1, &l1);
    scanf("%d %d %d", &s2, &t2, &l2);

    for (int i = 1; i <= n; i++)
        bfs(i);

    int mini = INF;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (dist[s1][i] + dist[i][j] + dist[j][t1] <= l1 && dist[s2][i] + dist[i][j] + dist[j][t2] <= l2)
                mini = min(mini, dist[s1][i] + dist[s2][i] + dist[i][j] + dist[j][t1] + dist[j][t2]);
            if (dist[s1][i] + dist[i][j] + dist[j][t1] <= l1 && dist[s2][j] + dist[i][j] + dist[i][t2] <= l2)
                mini = min(mini, dist[s1][i] + dist[s2][j] + dist[i][j] + dist[j][t1] + dist[i][t2]);
        }

    if (dist[s1][t1] <= l1 && dist[s2][t2] <= l2) mini = min(mini, dist[s1][t1] + dist[s2][t2]);

    if (mini == INF) printf("-1\n");
    else printf("%d\n", m - mini);

    return 0;
}
