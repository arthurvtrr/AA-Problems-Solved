#include <stdio.h>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

#define pii pair < int, int >
#define mp make_pair
#define INF 2000000000

vector < pii > graph[11000];

int dijkstra(int ini, int fim) {
    priority_queue < pair < int, pii > > fila;
    bool visited1[11000], visited2[11000];
    int dist1[11000], dist2[11000];
    for (int i = 0; i < 11000; i++) {
        visited1[i] = false;
        visited2[i] = false;
        dist1[i] = INF;
        dist2[i] = INF;
    }
    dist2[ini] = 0;
    fila.push(mp(-dist2[ini], mp(ini, 0)));
    while (!fila.empty()) {
        pii u = fila.top().second;
        fila.pop();
        if (u.second == 0) visited2[u.first] = true;
        else visited1[u.first] = true;

        for (pii v : graph[u.first]) {
            if (!visited1[v.first] && u.second == 0 && dist1[v.first] > dist2[u.first] + v.second) {
                dist1[v.first] = dist2[u.first] + v.second;
                fila.push(mp(-dist1[v.first], mp(v.first, 1)));
            }
            else if (!visited2[v.first] && u.second == 1 && dist2[v.first] > dist1[u.first] + v.second) {
                dist2[v.first] = dist1[u.first] + v.second;
                fila.push(mp(-dist2[v.first], mp(v.first, 0)));
            }
        }
    }

    if (dist2[fim] == INF) return -1;
    return dist2[fim];
}

int main() {
    int c, v, x, y, z;
    while (scanf("%d %d", &c, &v) != EOF) {
        for (int i = 0; i < 11000; i++)
            graph[i].clear();
        for (int i = 0; i < v; i++) {
            scanf("%d %d %d", &x, &y, &z);
            graph[x].push_back(mp(y,z));
            graph[y].push_back(mp(x,z));
        }
        int sol = dijkstra(1,c);
        printf("%d\n", sol);
    }
    return 0;
}
