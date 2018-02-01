#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000
#define N 5050

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

int t, r, c, lin[60][60], col[60][60];
char grid[60][60];
bool used[N][N];

int main() {
	scanf("%d", &t);
	for (int tc = 0; tc < t; tc++) {
		for (int i = 0; i < N; i++)
			graph[i].clear();

		for (int i = 0; i < 60; i++)
			for (int j = 0; j < 60; j++) {
				grid[i][j] = '.';
				lin[i][j] = col[i][j] = 0;
			}

		scanf("%d %d", &r, &c);

		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++)
				scanf(" %c", &grid[i][j]);

		int cont = 0;
		for (int i = 1; i <= r; i++)
			for (int j = 0; j <= c+1; j++) {
				if (grid[i][j] == '.') cont++;
				else col[i][j] = cont;
			}

		for (int i = 1; i <= c; i++)
			for (int j = 0; j <= r+1; j++) {
				if (grid[j][i] == '.') cont++;
				else lin[j][i] = cont;
			}

        vector < pair < int, int > > edges;

		for (int i = 0; i <= r+1; i++)
			for (int j = 0; j <= c+1; j++)
				if (grid[i][j] == '*') {
					if (!used[5040][lin[i][j]]) {
						addEdge(5040, lin[i][j], 1);
						used[5040][lin[i][j]] = true;
						edges.push_back({5040, lin[i][j]});
					}
					if (!used[lin[i][j]][col[i][j]]) {
						addEdge(lin[i][j], col[i][j], INF);
						used[lin[i][j]][col[i][j]] = true;
						edges.push_back({lin[i][j], col[i][j]});
					}
					if (!used[col[i][j]][5041]) {
						addEdge(col[i][j], 5041, 1);
						used[col[i][j]][5041] = true;
						edges.push_back({col[i][j], 5041});
					}
				}

		printf("%d\n", flow(5040, 5041));

		for (int i = 0; i < edges.size(); i++)
            used[edges[i].first][edges[i].second] = false;
	}

	return 0;
}
