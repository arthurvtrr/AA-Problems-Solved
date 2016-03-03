#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

#define INF 1000000000
typedef pair < int, int > pii;

void printPath(int previous[], int fim, int ini) {
    if (ini == fim) {
        printf("%d", ini);
        return;
    }
    printPath(previous, previous[fim], ini);
    printf(" %d", fim);
}

void dijkstra(vector < pii > graph[], int ini, int fim, int c) {
    priority_queue < pii > fila;
    bool visited[15];
    int dist[15];
    int previous[15];
    for (int i = 0; i < 15; i++) {
        dist[i] = INF;
        visited[i] = false;
        previous[i] = INF;
    }
    dist[ini] = 0;
    fila.push(make_pair(-dist[ini], ini));

    while(!fila.empty()) {
        int u = fila.top().second;
        fila.pop();
        visited[u] = true;
        for (pii v : graph[u]) {
            if (!visited[v.first] && dist[v.first] > dist[u] + v.second) {
                dist[v.first] = dist[u] + v.second;
                fila.push(make_pair(-dist[v.first], v.first));
                previous[v.first] = u;
            }
        }
    }

    printf("Case %d: Path = ", c);
    printPath(previous, fim, ini);
    printf("; %d second delay\n", dist[fim]);
}

int main() {
    int n, e, x, y, ini, fim, c = 0;
    while (scanf("%d", &n), n) {
        vector < pair < int, int > > region[15];

        for (int i = 1; i <= n; i++) {
            scanf("%d", &e);
            for (int j = 0; j < e; j++) {
                scanf("%d %d", &x, &y);
                region[i].push_back(make_pair(x,y));
            }
        }

        scanf("%d %d", &ini, &fim);
        dijkstra(region, ini, fim, ++c);
    }
    return 0;
}
