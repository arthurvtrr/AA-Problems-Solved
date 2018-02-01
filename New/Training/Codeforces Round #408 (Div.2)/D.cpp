#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >
#define INF 1000000000

int n, k, d, x, y, dist[300300];
bool station[300300];
set < int > graph[300300];
set < int > ans;
map < pii, int > ind;

void bfs() {
    for (int i = 0; i < 300300; i++)
        dist[i] = INF;

    queue < pii > fila;
    for (int i = 1; i <= n; i++)
        if (station[i]) {
            fila.push(pii(i, 0));
            dist[i] = 0;
        }

    while (!fila.empty()) {
        pii u = fila.front();
        fila.pop();

        for (int v : graph[u.first])
            if (dist[v] > dist[u.first] + 1) {
                dist[v] = dist[u.first] + 1;
                fila.push(pii(v, u.first));
            }
            else if (v != u.second) {
                ans.insert(ind[pii(u.first, v)]);
            }
    }
}

int main() {
    scanf("%d %d %d", &n, &k, &d);

    for (int i = 0; i < k; i++) {
        scanf("%d", &x);
        station[x] = true;
    }

    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        ind[pii(x, y)] = i+1;
        ind[pii(y, x)] = i+1;

        graph[x].insert(y);
        graph[y].insert(x);
    }

    bfs();

    printf("%d\n", ans.size());
    for (set < int >::iterator it = ans.begin(); it != ans.end(); it++) {
        if (it != ans.begin()) printf(" ");
        printf("%d", *it);
    }
    printf("\n");

    return 0;
}
