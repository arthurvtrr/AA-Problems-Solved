#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define INF 2000000000
#define N 10100

int nodes = N, ini, fim;
int dist[N], work[N];

struct Edge {
    int to, rev, used_flow, cap;
};

vector < Edge > graph[N];

void addEdge(int from, int to, int cap) {
    Edge a = {to, graph[to].size(), 0, cap};
    Edge b = {from, graph[from].size(), 0, 0};
    graph[from].push_back(a);
    graph[to].push_back(b);
}

bool dinic_bfs() {
    fill(dist, dist + nodes, -1);
    dist[ini] = 0;

    queue < int > fila;
    fila.push(ini);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            Edge &e = graph[u][i];
            int v = e.to;
            if (dist[v] < 0 && e.used_flow < e.cap) {
                dist[v] = dist[u] + 1;
                fila.push(v);
            }
        }
    }

    return dist[fim] >= 0;
}

int dinic_dfs(int u, int flow) {
    if (u == fim)
        return flow;

    for (int &i = work[u]; i < graph[u].size(); i++) {
        Edge &e = graph[u][i];

        if (e.cap > e.used_flow) {
            int v = e.to;

            if (dist[v] == dist[u] + 1) {
                int minf = dinic_dfs(v, min(flow, e.cap - e.used_flow));
                if (minf > 0) {
                    e.used_flow += minf;
                    graph[v][e.rev].used_flow -= minf;
                    return minf;
                }
            }
        }
    }

    return 0;
}

int flow(int _ini, int _fim) {
    ini = _ini;
    fim = _fim;
    int result = 0;

    while (dinic_bfs()) {
        fill(work, work + nodes, 0);
        while (int delta = dinic_dfs(ini, INT_MAX))
            result += delta;
    }

    return result;
}

#define ini 10090
#define fim 10091

int main() {
    int n;
    char tab[110][110];
    int pos[110][110];
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < N; i++)
            graph[i].clear();

        for (int i = 0; i < n; i++)
            scanf("%s", tab[i]);

        int aux = 0;
        char last = 'X';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (last == 'X' && tab[i][j] == '.') aux++;
                pos[i][j] = aux;
                last = tab[i][j];
            }
            last = 'X';
        }

        for (int i = 1; i <= aux; i++)
            addEdge(ini, i, 1);

        aux = 5000;
        last = 'X';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (last == 'X' && tab[j][i] == '.') aux++;
                if (tab[j][i] == '.')
                    addEdge(pos[j][i], aux, INF);
                last = tab[j][i];
            }
            last = 'X';
        }

        for (int i = 5001; i <= aux; i++)
            addEdge(i, fim, 1);

        printf("%d\n", flow(ini, fim));
    }
    return 0;
}
