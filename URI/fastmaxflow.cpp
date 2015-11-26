#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000

int nodes = 5050, ini, fim;
int dist[5050], q[5050], work[5050];

struct Edge {
    int to, rev, flowe, cap;
};

vector < Edge > graph[5050];

void addEdge(int from, int to, int cap) {
    Edge a = {to, graph[to].size(), 0, cap};
    Edge b = {from, graph[from].size(), 0, cap};
    graph[from].push_back(a);
    graph[to].push_back(b);
}

bool dinic_bfs() {
    fill(dist, dist + nodes, -1);
    dist[ini] = 0;
    int qt = 0;
    q[qt++] = ini;

    for (int qh = 0; qh < qt; qh++) {
        int u = q[qh];

        for (int i = 0; i < graph[u].size(); i++) {
            Edge &e = graph[u][i];
            int v = e.to;
            if (dist[v] < 0 && e.flowe < e.cap) {
                dist[v] = dist[u] + 1;
                q[qt++] = v;
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

        if (e.cap > e.flowe) {
            int v = e.to;

            if (dist[v] == dist[u] + 1) {
                int minf = dinic_dfs(v, min(flow, e.cap - e.flowe));
                if (minf > 0) {
                    e.flowe += minf;
                    graph[v][e.rev].flowe -= minf;
                    return minf;
                }
            }
        }
    }

    return 0;
}

long long flow(int _ini, int _fim) {
    ini = _ini;
    fim = _fim;
    long long result = 0;

    while (dinic_bfs()) {
        fill(work, work + nodes, 0);
        while (int delta = dinic_dfs(ini, INT_MAX))
            result += delta;
    }

    return result;
}

int main() {
    int n, m, x, y, z;

    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        if (x != y) addEdge(x, y, z);
    }

    printf("%lld\n", flow(1, n));
    return 0;
}
