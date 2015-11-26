#include <bits/stdc++.h>

using namespace std;

#define INF 100000000

int roads[3300][3300];
vector < int > r[3300];

int main() {
    int n, m, x, y, s1, s2, t1, t2, l1, l2;
    scanf("%d %d", &n, &m);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            roads[i][j] = -1;

    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &x, &y);
        r[x].push_back(y);
        r[y].push_back(x);
    }

    scanf("%d %d %d", &s1, &t1, &l1);
    scanf("%d %d %d", &s2, &t2, &l2);

    for (int i = 1; i <= n; i++) {
        queue < int > fila;
        fila.push(i);
        roads[i][i] = 0;
        while (!fila.empty()) {
            int u = fila.front();
            fila.pop();

            for (int j = 0; j < r[u].size(); j++) {
                if (roads[i][r[u][j]] == -1) {
                    roads[i][r[u][j]] = roads[i][u] + 1;
                    fila.push(r[u][j]);
                }
            }
        }
    }

    int s = m + 1;
    for (int t = 0; t < 2; t++) {
        swap(s1, t1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (roads[s1][i] + roads[i][j] + roads[j][t1] <= l1 && roads[s2][i] + roads[i][j] + roads[j][t2] <= l2)
                    s = min(s, roads[s1][i] + roads[i][j] + roads[j][t1] + roads[s2][i] + roads[j][t2]);
            }
        }
    }

    if (roads[s1][t1] <= l1 && roads[s2][t2] <= l2)
        s = min(s, roads[s1][t1] + roads[s2][t2]);

    if (s > m) printf("-1\n");
    else printf("%d\n", m - s);

    return 0;
}
