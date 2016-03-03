#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000

int flow(int ini, int fim, int n, vector < int > *graph, int **cap) {
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
                if(!used[v] and cap[u][v] > 0) {
                    previous[v] = u;
                    fila.push(v);
                }
        }

        if (previous[fim] == -1) break;
        int minimum = INT_MAX, u = fim;

        while (previous[u] != -1) {
            minimum = min(cap[previous[u]][u], minimum);
            u = previous[u];
        }

        answer += minimum;
        u = fim;

        while (previous[u] != -1) {
            cap[previous[u]][u] -= minimum;
            cap[u][previous[u]] += minimum;
            u = previous[u];
        }
    }

    return answer;
}

#define ini 218
#define fim 219

int main() {
    int n, m, b, d, x, y, z;

    while (scanf("%d", &n) != EOF) {
        vector < int > connections[220];
        int **cap = new int*[220];
        for (int i = 0; i < 220; i++)
            cap[i] = new int[220];

        for (int i = 0; i < 220; i++)
            for (int j = 0; j < 220; j++)
                cap[i][j] = 0;

        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            connections[i].push_back(i+n);
            connections[i+n].push_back(i);
            cap[i][i+n] = x;
            cap[i+n][i] = x;
        }

        scanf("%d", &m);

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &z);
            connections[x+n].push_back(y);
            connections[y+n].push_back(x);
            cap[x+n][y] = z;
            cap[y+n][x] = z;
        }

        scanf("%d %d", &b, &d);
        for (int i = 0; i < b; i++) {
            scanf("%d", &x);
            connections[ini].push_back(x);
            connections[x+n].push_back(ini);
            cap[ini][x] = INF;
            cap[x+n][ini] = INF;
        }
        for (int i = 0; i < d; i++) {
            scanf("%d", &x);
            connections[x+n].push_back(fim);
            connections[fim].push_back(x);
            cap[x+n][fim] = INF;
            cap[fim][x] = INF;
        }

        printf("%d\n", flow(ini, fim, 220, connections, cap));

    }
    return 0;
}
