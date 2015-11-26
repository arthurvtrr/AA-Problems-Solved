#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <math.h>
#include <queue>

#define INF 100000000

using namespace std;

int Dijkstra(vector < int > g[], int w[], int s, int n, int f) {
    priority_queue < pair < int, int > > fila;
    int d[n+1];
    bool visited[n+1];
    for (int i = 1; i <= n; i++) {
        d[i] = INF;
        visited[i] = false;
    }

    d[s] = w[s];
    fila.push(make_pair(-d[s], s));

    while (!fila.empty()) {
        int u = fila.top().second;
        visited[u] = true;
        fila.pop();

        for (int v : g[u]) {
            if (!visited[v] && d[u] + w[v] < d[v]) {
                d[v] = d[u] + w[v];
                fila.push(make_pair(-d[v], v));
            }
        }
    }

    return d[f];
}

int main() {
    int n, m, k, x, y, z, a, s, f, w[1100];
    double p;
    while (scanf("%d %d %d %lf", &n, &m, &k, &p) != EOF) {
        vector < int > roads[1100];
        memset(w, 0, sizeof(w));
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            roads[x].push_back(y);
            roads[y].push_back(x);
        }

        scanf("%d", &a);
        for (int i = 0; i < a; i++) {
            scanf("%d", &z);
            w[z]++;
        }

        scanf("%d %d", &s, &f);
        int soldiers = Dijkstra(roads, w, s, n, f);
        if (k < soldiers) printf("0.000\n");
        else printf("%.3f\n", pow(p, soldiers));
    }

    return 0;
}
