#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define INF 2000000000
#define N 100100
#define AUX 50010

int n, m, p, a, b;
int pairU[AUX], pairV[AUX], dist[AUX];
vector < int > graph[N];

bool hopBfs() {
    queue < int > fila;

    for (int u = 1; u <= n; u++) {
        if (pairU[u] == 0) {
            dist[u] = 0;
            fila.push(u);
        }
        else dist[u] = INF;
    }

    dist[0] = INF;

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        if (dist[u] < dist[0])
            for (int v : graph[u])
                if (dist[pairV[v-AUX]] == INF) {
                    dist[pairV[v-AUX]] = dist[u] + 1;
                    fila.push(pairV[v-AUX]);
                }
    }

    return dist[0] != INF;
}

bool hopDfs(int u) {
    if (u == 0) return true;

    for (int v : graph[u])
        if (dist[pairV[v-AUX]] == dist[u] + 1)
            if (hopDfs(pairV[v-AUX])) {
                pairV[v-AUX] = u;
                pairU[u] = v;
                return true;
            }

    dist[u] = INF;
    return false;
}

int hopcroft() {
    int result = 0;

    while (hopBfs())
        for (int u = 1; u <= n; u++)
            if (pairU[u] == 0 && hopDfs(u))
                result++;

    return result;
}

int main() {
    scanf("%d %d %d", &n, &m, &p);

    for (int i = 0; i < p; i++) {
        scanf("%d %d", &a, &b);
        graph[a].push_back(b+AUX);
        graph[b+AUX].push_back(a);
    }

    printf("%d\n", hopcroft());

    return 0;
}
