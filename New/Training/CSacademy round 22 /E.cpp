#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000
#define pii pair < int, int >

int n, k, x;
bool valid[1010];
int dist[2020][1010];

void bfs() {
    for (int i = 0; i < 2020; i++)
        for (int j = 0; j < 1010; j++)
            dist[i][j] = INF;

    queue < pii > fila;

    dist[0][0] = 0;
    fila.push(pii(0, 0));

    while (!fila.empty()) {
        pii u = fila.front();
        fila.pop();

        for (int i = 0; i < 1010; i++)
            if (valid[i] && dist[(u+i)/2] > dist[u] + 1) {
                dist[(u+i)/2] = dist[u] + 1;
                fila.push((u+i)/2);
            }
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &x);
        valid[x] = true;
    }

    bfs();
    printf("%d\n", dist[n] == INF? -1 : dist[n]);

    return 0;
}
