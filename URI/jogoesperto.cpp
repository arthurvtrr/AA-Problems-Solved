#include <stdio.h>
#include <queue>
#include <map>

using namespace std;

#define INF 1000000000

int bfs(int n, int m) {
    queue < int > fila;
    map < int, int > dist;
    map < int, bool > vst;

    for (int i = -50005; i < 50006; i++) {
        dist[i] = INF;
        vst[i] = false;
    }

    dist[n] = 0;
    fila.push(n);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();
        vst[u] = true;
        if (u*2 <= 50000 && !vst[u*2] && dist[u*2] > 1 + dist[u]) {
            dist[u*2] = 1 + dist[u];
            fila.push(u*2);
        }
        if (u*3 <= 50000 && !vst[u*3] && dist[u*3] > 1 + dist[u]) {
            dist[u*3] = 1 + dist[u];
            fila.push(u*3);
        }
        if (u/2 <= 50000 && !vst[u/2] && dist[u/2] > 1 + dist[u]) {
            dist[u/2] = 1 + dist[u];
            fila.push(u/2);
        }
        if (u/3 <= 50000 && !vst[u/3] && dist[u/3] > 1 + dist[u]) {
            dist[u/3] = 1 + dist[u];
            fila.push(u/3);
        }
        if (u+7 <= 50000 && !vst[u+7] && dist[u+7] > 1 + dist[u]) {
            dist[u+7] = 1 + dist[u];
            fila.push(u+7);
        }
        if (u-7 >= -50000 && !vst[u-7] && dist[u-7] > 1 + dist[u]) {
            dist[u-7] = 1 + dist[u];
            fila.push(u-7);
        }
    }

    return dist[m];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    printf("%d\n", bfs(n,m));
    return 0;
}
