#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>

using namespace std;

#define INF 2000000000
#define N 2200
#define AUX 1010

int n;
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
    int t, m, a, b;
    scanf("%d", &t);

    while (t--) {
        for (int i = 0; i < AUX; i++)
            pairU[i] = pairV[i] = 0;
        for (int i = 0; i < N; i++)
            graph[i].clear();

        scanf("%d", &m);

        map < int, int > indx, indy;
        int x = 1, y = 1+AUX;

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            if (!indx.count(a))
                indx[a] = x++;
            if (!indy.count(b))
                indy[b] = y++;

            graph[indx[a]].push_back(indy[b]);
            graph[indy[b]].push_back(indx[a]);
        }
        n = x-1;

        printf("%d\n", hopcroft());
    }
    return 0;
}
