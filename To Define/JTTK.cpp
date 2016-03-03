#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define INF 1000000000

struct cell {
    int x;
    int y;
};

int cost[550][550];
bool visited[550][550];
vector < cell > graph[550][550];
int dist[550][550];

int Dijkstra(cell s, cell f) {
    priority_queue < pair < int, cell > > fila;
    for (int i = 0; i < 550; i++) {
        for (int j = 0; j < 550; j++) {
            visited[i][j] = false;
            dist[i][j] = INF;
        }
    }

    dist[s.x][s.y] = 0;
    fila.push(make_pair(-dist[s.x][s.y], s));

    while (!fila.empty()) {
        cell u = fila.top().second;
        visited[u.x][u.y] = true;
        fila.pop();

        for (cell v : graph[u.x][u.y]) {
            if (!visited[v.x][v.y] && dist[v.x][v.y] > dist[u.x][u.y] + cost[v.x][v.y]) {
                dist[v.x][v.y] = dist[u.x][u.y] + cost[v.x][v.y];
                fila.push(make_pair(-dist[v.x][v.y], v));
            }
        }
    }
    return dist[f.x][f.y];
}

int main() {
    int r, c, n;
    while (scanf("%d %d %d", &r, &c, &n) != EOF) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                scanf("%d", cost[i][j]);
                graph[i][j].clear();
            }
        }

    }
    return 0;
}
