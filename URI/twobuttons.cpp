#include <stdio.h>
#include <queue>

using namespace std;

#define INF 1000000000

bool visited[1100000];
int dist[1100000];

int bfs(int ini, int fim) {
    queue < int > fila;
    for (int i = 0; i < 1100000; i++) {
        visited[i] = false;
        dist[i] = INF;
    }
    dist[ini] = 0;
    fila.push(ini);
    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();
        visited[u] = true;

        if (u * 2 < 1100000 && !visited[u * 2] && dist[u * 2] > dist[u] + 1) {
            dist[u * 2] = dist[u] + 1;
            fila.push(u*2);
        }
        if (u - 1 > 0 && !visited[u - 1] && dist[u - 1] > dist[u] + 1) {
            dist[u - 1] = dist[u] + 1;
            fila.push(u-1);
        }
    }

    return dist[fim];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%d\n", bfs(n, m));
    return 0;
}
