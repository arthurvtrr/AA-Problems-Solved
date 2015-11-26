#include <stdio.h>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int bfs(map < int, vector < int > > graph, int s, int limit) {
    queue < int > fila;
    map < int, int > dist;
    map < int, bool > visited;
    dist[s] = 0;
    queue.push(s);
    visited[s] = true;

    while (!fila.empty()) {
        int u = fila.top();
        fila.pop();
        for (int v : graph[u]) {
            if (!visited[v] && dist[v] > dist[u] + 1)
                dist[v]
        }
    }

}

int main() {
    int n, x, y, s, ttl;
    while(scanf("%d", &n), n) {
        map < int, vector < int > > network;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            network[x].push_back(y);
            network[y].push_back(x);
        }

        while (scanf("%d %d", &s, &ttl), s || ttl) {

        }
    }

    return 0;
}
