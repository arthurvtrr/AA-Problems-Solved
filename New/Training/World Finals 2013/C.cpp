#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >
#define INF 1000000000
#define N 25500

int n, m, c, x, y, t, quant[N];
vector < pii > origGraph[N];
int distd[N];

void dijkstra() {
    for (int i = 0; i < N; i++) distd[i] = INF;
    priority_queue < pii > fila;
    distd[1] = 0;
    fila.push(pii(0, 1));

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();
        for (pii v : origGraph[u])
            if (distd[v.first] > distd[u] + v.second) {
                distd[v.first] = distd[u] + v.second;
                fila.push(pii(-distd[v.first], v.first));
            }
    }
}

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

int main() {
    scanf("%d %d %d", &n, &m, &c);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &t);
        origGraph[x].push_back(pii(y, t));
        origGraph[y].push_back(pii(x, t));
    }
    for (int i = 0; i < c; i++) {
        scanf("%d", &x);
        quant[x]++;
    }

    dijkstra();

    set < int > dists;
    for (int i = 1; i <= n; i++)
        if (quant[i])
            dists.insert(distd[i]);

    int ans = 0;
    for (auto d : dists) {
        for (int i = 0; i < N; i++) graph[i].clear();

        for (int i = 1; i <= n; i++)
            for (int j = 0; j < origGraph[i].size(); j++) {
                int a = origGraph[i][j].first, b = origGraph[i][j].second;
                if (distd[a] == distd[i] + b && distd[a] <= d)
                    addEdge(a, i, 1);
            }

        for (int i = 1; i <= n; i++)
            if (distd[i] == d)
                addEdge(n+1, i, quant[i]);

        ans += flow(n+1, 1);
    }
    printf("%d\n", ans);

    return 0;
}

