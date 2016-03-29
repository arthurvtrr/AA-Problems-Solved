#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define INF 2000000000
#define N 250

int res[N][N];
vector < int > graph[N];

int flow(int ini, int fim, int n) {
    int answer = 0;
    int previous[n];
    bool used[n];

    while(true) {
        fill(used, used+n, false);
        fill(previous, previous+n, -1);

        queue < int > fila;
        fila.push(ini);

        while(!fila.empty()) {
            int u = fila.front();
            used[u] = true;
            fila.pop();

            for(int v : graph[u])
                if(!used[v] and res[u][v] > 0) {
                    previous[v] = u;
                    fila.push(v);
                }
        }

        if (previous[fim] == -1) break;
        int minimum = INT_MAX, u = fim;

        while (previous[u] != -1) {
            minimum = min(res[previous[u]][u], minimum);
            u = previous[u];
        }

        answer += minimum;
        u = fim;

        while (previous[u] != -1) {
            res[previous[u]][u] -= minimum;
            res[u][previous[u]] += minimum;
            u = previous[u];
        }
    }

    return answer;
}

#define ini 248
#define fim 249

int main() {
    int t, n, x, y;
    scanf("%d", &t);

    for (int tc = 0; tc < t; tc++) {
        for (int i = 0; i < N; i++) {
            graph[i].clear();
            for (int j = 0; j < N; j++)
                res[i][j] = 0;
        }

        scanf("%d", &n);

        for (int i = 0; i < 120; i++) {
            graph[ini].push_back(i);
            graph[i].push_back(ini);
            res[ini][i] = 1;
            graph[i+120].push_back(fim);
            graph[fim].push_back(i+120);
            res[i+120][fim] = 1;
        }

        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &x, &y);
            graph[x].push_back(y+120);
            graph[y+120].push_back(x);
            res[x][y+120] = 1;
        }

        printf("%d\n", flow(ini, fim, N));
    }

    return 0;
}

