#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000
#define N 120
#define pii pair < int, int >

int nodes = N, ini, fim;
int dist[N], work[N];

struct Edge {
    int to, rev, used_flow, cap, cost;
};

vector < Edge > graph[N];

void addEdge(int from, int to, int cap, int cost) {
    Edge a = {to, graph[to].size(), 0, cap, cost};
    Edge b = {from, graph[from].size(), 0, 0, 0};
    graph[from].push_back(a);
    graph[to].push_back(b);
}

bool dinic_bfs() {
    for (int i = 0; i < nodes; i++)
        dist[i] = INF;

    dist[ini] = 0;

    for (int i = 0; i < nodes-1; i++)
        for (int u = 0; u < nodes; u++)
            for (int j = 0; j < graph[u].size(); j++) {
                Edge &e = graph[u][j];
                if (dist[u] != INF && dist[e.to] > dist[u] + e.cost && e.used_flow < e.cap)
                    dist[e.to] = dist[u] + e.cost;
            }

    return dist[fim] < INF;
}

pii dinic_dfs(int u, int flow, int cost) {
    if (u == fim)
        return make_pair(flow, cost);

    for (int &i = work[u]; i < graph[u].size(); i++) {
        Edge &e = graph[u][i];

        if (e.cap > e.used_flow) {
            int v = e.to;

            if (dist[v] == dist[u] + e.cost) {
                pii minf = dinic_dfs(v, min(flow, e.cap - e.used_flow), cost + e.cost);
                if (minf.first > 0) {
                    e.used_flow += minf.first;
                    graph[v][e.rev].cost -= e.cost;
                    graph[v][e.rev].used_flow -= minf.first;
                    return minf;
                }
            }
        }
    }

    return make_pair(0, 0);
}

int minCost(int _ini, int _fim) {
    ini = _ini;
    fim = _fim;
    int cost = 0;

    while (dinic_bfs()) {
        fill(work, work + nodes, 0);
        while (1) {
            pii delta = dinic_dfs(ini, INT_MAX, 0);
            if (delta == make_pair(0, 0)) break;
            cost = max(cost, delta.second);
        }
    }

    return cost;
}

int t, n, e, b, x, y, cont, supply[N], energy[N];

vector < int > aux[N], regions;
int dfs_num[N], dfs_low[N], dfs_parent[N], art_point[N], dfsCont, dfsRoot, rootChildren;
bool visited[N];

void artic_points(int u) {
    dfs_low[u] = dfs_num[u] = dfsCont++;
    for (int v : aux[u]) {
        if (!dfs_num[v]) {
            dfs_parent[v] = u;
            if (u == dfsRoot) rootChildren++;

            artic_points(v);

            if (dfs_low[v] >= dfs_num[u])
                art_point[u] = true;
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (v != dfs_parent[u])
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

pair < vector < int >, int > used[N];

void dfs(int u) {
    visited[u] = true;
    used[cont].first.push_back(u);

    for (int v : aux[u]) {
        if (!visited[v])
            dfs(v);
        else if (art_point[v]) {
            if (used[cont].second == 0) used[cont].second = v;
            else if (v != used[cont].second) used[cont].second = -1;
            else used[cont].second += 10000;
        }
    }
}

#define source 0
#define sink N-1

int main() {
	scanf("%d", &t);
	for (int tc = 0; tc < t; tc++) {

		for (int i = 0; i < N; i++) {
			graph[i].clear();
			aux[i].clear();
			visited[i] = false;
			dfs_num[i] = dfs_low[i] = dfs_parent[i] = art_point[i] = 0;
		}

		scanf("%d %d %d", &n, &e, &b);
		for (int i = 1; i <= n; i++)
			scanf("%d", &supply[i]);
		for (int i = 1; i <= b; i++)
			scanf("%d", &energy[i]);

		for (int i = 0; i < e; i++) {
			scanf("%d %d", &x, &y);
			aux[x].push_back(y);
			aux[y].push_back(x);
		}

		dfsCont = 1;
        for (int i = 1; i <= n; i++)
            if (!dfs_num[i]) {
                dfsRoot = i; rootChildren = 0; artic_points(i);
                art_point[dfsRoot] = (rootChildren > 1);
            }

        regions.clear();
        for (int i = 1; i <= n; i++)
            visited[i] = art_point[i];

        while (1) {
            int left = n;
            for (int i = 1; i <= n; i++) left -= visited[i];
            if (left == 0) break;

            cont = 0;
            for (int i = 1; i <= n; i++)
                if (!visited[i]) {
                    cont++;
                    dfs(i);
                }

            for (int i = 1; i <= cont; i++) {
                if (used[i].second >= 0) {
                    int sum = 0;
                    for (int v : used[i].first)
                        sum += supply[v];

                    bool cycle = used[i].second > 10000;
                    if (cycle) used[i].second -= 10000;

                    if (cycle) sum += supply[used[i].second];
                    visited[used[i].second] = art_point[used[i].second] = false;
                    regions.push_back(sum);
                }
                else {
                    for (int v : used[i].first)
                        visited[v] = false;
                }
                used[i].first.clear();
                used[i].second = 0;
            }
        }

        if (regions.size() > b) printf("Buzz Mission %d: %d No\n", tc+1, regions.size());
        else {
            for (int i = 1; i <= b; i++)
                addEdge(source, i, 1, 0);
            for (int i = 0; i < regions.size(); i++)
                addEdge(i+60, sink, 1, 0);
            for (int i = 1; i <= b; i++)
                for (int j = 0; j < regions.size(); j++)
                    addEdge(i, j+60, 1, abs(regions[j]-energy[i]));

            int ans = minCost(source, sink);
            printf("Buzz Mission %d: %d %d\n", tc+1, regions.size(), ans);
        }
	}

	return 0;
}

