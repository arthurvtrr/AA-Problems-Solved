#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000
#define N 550
#define pii pair <int, int>

int nodes = N, ini, fim;
int dist[N], work[N];

struct Edge {
    int to, rev, used_flow, cap;
};

vector < Edge > graph[N];

void addEdge(int from, int to, int cap) {
    Edge a = {to, graph[to].size(), 0, cap};
    Edge b = {from, graph[from].size(), 0, cap};
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

int t, n, m, k, x, y, marks[N];
bool fix[N], visited[N];
vector < pii > edges;

#define source 540
#define sink 541

void dfs(int u, int pot) {
    visited[u] = true;
    marks[u] |= 1 << pot;

    for (Edge v : graph[u])
        if (!visited[v.to] && v.used_flow != v.cap)
            dfs(v.to, pot);
}

int main() {
	scanf("%d", &t);
	for (int tc = 0; tc < t; tc++) {
        for (int i = 0; i < N; i++) {
            fix[i] = false;
            marks[i] = 0;
        }
        edges.clear();

		scanf("%d %d", &n, &m);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			edges.push_back(make_pair(x, y));
        }

        scanf("%d", &k);
		for (int i = 0; i < k; i++) {
			scanf("%d %d", &x, &y);
            marks[x] = y;
            fix[x] = true;
        }

        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < N; j++)
                graph[j].clear();

            for (int j = 1; j <= n; j++) {
                if (marks[j] & (1 << i))
                    addEdge(source, j, INF);
                else
                    addEdge(j, sink, fix[j]? INF : 0);
            }
            for (int j = 0; j < edges.size(); j++)
                addEdge(edges[j].first, edges[j].second, 1);

            flow(source, sink);

            for (int j = 0; j < N; j++)
                visited[j] = false;

            dfs(source, i);
        }

        for (int i = 1; i <= n; i++)
            printf("%d\n", marks[i]);
	}

	return 0;
}
