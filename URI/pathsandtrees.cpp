#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

#define INF 9110000000
typedef pair < int, int > pii;
vector < pii > region[330000];
map < pii, int > edges;
long long total = 0;

void dijkstra(int ini) {
    priority_queue < pii > fila;
    vector < int > indexes;
    bool visited[330000];
    int dist[330000];
    int previous[330000];
    for (int i = 0; i < 330000; i++) {
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

        for (pii v : region[u]) {
            if (!visited[v.first] && dist[v.first] > dist[u] + v.second) {
                dist[v.first] = dist[u] + v.second;
                fila.push(make_pair(-dist[v.first], v.first));
                previous[v.first] = u;
                total += v.second;
                int i = edges[make_pair(u, v.first)];
                indexes.push_back(i);
            }
        }
    }

    printf("%lld\n", total);
    for (int i = 0; i < indexes.size(); i++) {
        printf("%d", indexes[i]);
        if (i < indexes.size() - 1) printf(" ");
    }
    if (total > 0) printf("\n");
}

int main() {
    int n, m, u, v, w, ini;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &u, &v, &w);
        region[v].push_back(make_pair(u, w));
        region[u].push_back(make_pair(v, w));
        edges[make_pair(u, v)] = i;
        edges[make_pair(v, u)] = i;
    }

    scanf("%d", &ini);
    dijkstra(ini);

    return 0;
}

