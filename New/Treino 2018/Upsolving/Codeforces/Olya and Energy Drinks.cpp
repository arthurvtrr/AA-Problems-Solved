#include <bits/stdc++.h>

using namespace std;

#define INF 100000000
#define pii pair < int, int >

int n, m, k, a, b, c, d;
char grid[1010][1010];

bool visited[1010][1010];
int dist[1010][1010];

void bfs() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist[i][j] = INF;

    queue < pii > fila;
    fila.push(pii(a, b));
    dist[a][b] = 0;
    visited[a][b] = true;

    while (!fila.empty()) {
        pii u = fila.front();
        fila.pop();

        int dt = 1;
        while (dt <= k && u.first - dt >= 0 && grid[u.first - dt][u.second] != '#' && dist[u.first - dt][u.second] >= dist[u.first][u.second] + 1) {
            if (visited[u.first - dt][u.second]) { dt++; continue; }
            visited[u.first - dt][u.second] = true;
            dist[u.first - dt][u.second] = dist[u.first][u.second] + 1;
            fila.push(pii(u.first - dt, u.second));
            dt++;
        }
        dt = 1;
        while (dt <= k && u.first + dt < n && grid[u.first + dt][u.second] != '#' && dist[u.first + dt][u.second] >= dist[u.first][u.second] + 1) {
            if (visited[u.first + dt][u.second]) { dt++; continue; }
            visited[u.first + dt][u.second] = true;
            dist[u.first + dt][u.second] = dist[u.first][u.second] + 1;
            fila.push(pii(u.first + dt, u.second));
            dt++;
        }
        dt = 1;
        while (dt <= k && u.second - dt >= 0 && grid[u.first][u.second - dt] != '#' && dist[u.first][u.second - dt] >= dist[u.first][u.second] + 1) {
            if (visited[u.first][u.second - dt]) { dt++; continue; }
            visited[u.first][u.second - dt] = true;
            dist[u.first][u.second - dt] = dist[u.first][u.second] + 1;
            fila.push(pii(u.first, u.second - dt));
            dt++;
        }
        dt = 1;
        while (dt <= k && u.second + dt < m && grid[u.first][u.second + dt] != '#' && dist[u.first][u.second + dt] >= dist[u.first][u.second] + 1) {
            if (visited[u.first][u.second + dt]) { dt++; continue; }
            visited[u.first][u.second + dt] = true;
            dist[u.first][u.second + dt] = dist[u.first][u.second] + 1;
            fila.push(pii(u.first, u.second + dt));
            dt++;
        }
    }

    printf("%d\n", dist[c][d] == INF? -1 : dist[c][d]);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++)
        scanf("%s", grid[i]);
    scanf("%d %d %d %d", &a, &b, &c, &d);
    a--; b--; c--; d--;

    bfs();
    return 0;
}
