#include <bits/stdc++.h>

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

int n, m;

struct p {
    int x, y;
} ps[5050];

#define source 10097
#define sink 10098

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &ps[i].x, &ps[i].y);
        addEdge(source, i + 5050, 1);
        addEdge(i + 5050, ps[i].x, 1);
        addEdge(i + 5050, ps[i].y, 1);
    }

    for (int i = 1; i <= n; i++)
        addEdge(i, sink, 1);

    int ini = 0, fim = 5050;
    while (ini <= fim) {
        int mid = (ini + fim) / 2;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < graph[i].size(); j++) {
                graph[i][j].used_flow = 0;
                if (graph[i][j].to == sink)
                    graph[i][j].cap = mid;
            }

        int x = flow(source, sink);
        if (x == m) fim = mid-1;
        else ini = mid+1;
    }
    printf("%d\n", ini);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < graph[i].size(); j++) {
            graph[i][j].used_flow = 0;
            if (graph[i][j].to == sink)
                graph[i][j].cap = ini;
        }

    flow(source, sink);

    for (int i = 0; i < m; i++) {
        if (graph[i+5050][1].used_flow == 1) printf("%d %d\n", ps[i].x, ps[i].y);
        else printf("%d %d\n", ps[i].y, ps[i].x);
    }

    return 0;
}
