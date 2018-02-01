#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >
#define ll long long
#define INF 1000000000000LL
#define tri pair < int, pii >

int n, m, x, y, z;
vector < pii > graph[100100];
ll dist[100100], dist1[100100];
int previous[100100];
set < pii > used;

void bfs() {
    for (int i = 0; i < 100100; i++)
        dist[i] = INF;
    dist[1] = 0;
    queue < int > fila;
    fila.push(1);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (pii v : graph[u])
            if (dist[v.first] > dist[u] + 1) {
                dist[v.first] = dist[u] + 1;
                fila.push(v.first);
            }
    }
}

void dijkstra() {
    for (int i = 0; i < 100100; i++) {
        dist1[i] = INF;
        previous[i] = -1;
    }

    dist1[1] = 0;
    priority_queue < tri > fila;
    fila.push(tri(0, pii(0, 1)));

    while (!fila.empty()) {
        pii u = fila.top().second;
        ll dt = -fila.top().first;
        fila.pop();

        for (pii v : graph[u.second])
            if (u.first+1 == dist[v.first] && dist1[v.first] > dt + (v.second == 0? 1000000LL : 1LL)) {
                dist1[v.first] = dt + (v.second == 0? 1000000LL : 1LL);
                previous[v.first] = u.second;
                fila.push(tri(-dist1[v.first], pii(u.first+1, v.first)));
            }
    }

    int aux = n;
    while (previous[aux] != -1) {
        used.insert(pii(min(aux, previous[aux]), max(aux, previous[aux])));
        aux = previous[aux];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        graph[x].push_back(pii(y,z));
        graph[y].push_back(pii(x,z));
    }

    bfs();
    dijkstra();

    vector < pii > rem, add;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < graph[i].size(); j++) {
            int a = i, b = graph[i][j].first;
            if (a > b) continue;

            if (graph[i][j].second == 0 && used.count(pii(a, b)))
                add.push_back(pii(a, b));
            else if (graph[i][j].second == 1 && !used.count(pii(a, b)))
                rem.push_back(pii(a, b));
        }

    printf("%d\n", rem.size() + add.size());
    for (int i = 0; i < rem.size(); i++)
        printf("%d %d 0\n", rem[i].first, rem[i].second);
    for (int i = 0; i < add.size(); i++)
        printf("%d %d 1\n", add[i].first, add[i].second);

    return 0;
}
