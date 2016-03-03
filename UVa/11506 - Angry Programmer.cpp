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

int main() {
    int m, w, x, y, z;

    while (scanf("%d %d", &m, &w), m || w) {
        vector < int > connections[110];
        int **cap = new int*[110];
        for (int i = 0; i < 110; i++)
            cap[i] = new int[110];

        for (int i = 0; i < 110; i++)
            for (int j = 0; j < 110; j++)
                cap[i][j] = 0;

        for (int i = 0; i < m-2; i++) {
            scanf("%d %d", &x, &y);
            connections[x].push_back(x+m);
            connections[x+m].push_back(x);
            cap[x][x+m] = y;
        }

        connections[1].push_back(1+m);
        connections[1+m].push_back(1);
        connections[m].push_back(m+m);
        connections[m+m].push_back(m);
        cap[1][1+m] = INF;
        cap[m][m+m] = INF;

        for (int i = 0; i < w; i++) {
            scanf("%d %d %d", &x, &y, &z);
            connections[x+m].push_back(y);
            connections[y].push_back(x+m);
            connections[y+m].push_back(x);
            connections[x].push_back(y+m);
            cap[x+m][y] = z;
            cap[y+m][x] = z;
        }

        printf("%d\n", flow(1, m, 110, connections, cap));
    }

    return 0;
}
