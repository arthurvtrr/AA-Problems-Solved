#include <bits/stdc++.h>

using namespace std;

#define pdi pair < double, int >
#define N 440
#define INF 1e12

int n, m, x[N], y[N], z[N], holes[N], a, b;
set < int > heights;
double dist[N][N], cDist[N][N];

vector < int > graph[N];
int comp[N], cHoles[N];

void dfs(int u, int c, int h) {
    comp[u] = c;
    cHoles[c] += holes[u];

    for (int v : graph[u])
        if (!comp[v] && z[v] <= h)
            dfs(v, c, h);
}

double best[N];
bool visited[N];

double dijkstra(int nc) {
    for (int i = 1; i <= nc; i++) {
        best[i] = INF;
        visited[i] = false;
    }

    priority_queue < pdi > fila;
    best[comp[1]] = cHoles[comp[1]] * 0.5;
    fila.push(pdi(-best[comp[1]], comp[1]));

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();
        visited[u] = true;

        for (int i = 1; i <= nc; i++)
            if (!visited[i] && best[i] > best[u] + cDist[u][i]) {
                best[i] = best[u] + cDist[u][i];
                fila.push(pdi(-best[i], i));
            }
    }
    return best[comp[n]];
}

int main() {
    int t = 1;
    while (scanf("%d %d", &n, &m) != EOF) {
        heights.clear();
        for (int i = 0; i < N; i++)
            graph[i].clear();

        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d %d", &x[i], &y[i], &z[i], &holes[i]);
            heights.insert(z[i]);
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]) + (z[i] - z[j])*(z[i] - z[j]));

        double ans = INF;
        for (auto h : heights) {
            if (h < max(z[1], z[n])) continue;

            for (int i = 1; i <= n; i++) comp[i] = cHoles[i] = 0;

            int c = 1;
            for (int i = 1; i <= n; i++)
                if (z[i] <= h && !comp[i]) {
                    dfs(i, c, h);
                    c++;
                }

            if (comp[1] == comp[n]) {
                ans = min(ans, cHoles[comp[1]] * 0.5);
                continue;
            }

            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    cDist[i][j] = INF;

            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++) {
                    if (holes[i] == 0 || holes[j] == 0 || comp[i] == comp[j]) continue;
                    if (comp[j] != comp[n] && cHoles[comp[j]] < 2) continue;

                    cDist[comp[i]][comp[j]] = min(cDist[comp[i]][comp[j]], cHoles[comp[j]] * 0.5 - 1 + dist[i][j]);
                }

            ans = min(ans, dijkstra(c-1));
        }

        if (ans > INF - 1) printf("Case %d: impossible\n", t++);
        else printf("Case %d: %.4f\n", t++, ans);
    }

    return 0;
}

/*
7 6
2 0 1 1
0 0 0 2
1 0 4 3
3 0 4 3
5 0 1 1
3 0 2 0
5 0 3 0
1 2
1 3
3 4
4 7
5 7
6 7
*/
