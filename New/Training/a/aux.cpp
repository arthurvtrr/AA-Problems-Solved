#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000
#define N 500
#define pii pair < int, int >

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

int t, n, e, b, x, y, cont, supply[N], energy[N];

vector < int > aux[N], regions;
int dfs_num[N], dfs_low[N], dfs_parent[N], art_point[N], dfsCont, dfsRoot, rootChildren;
bool visited[N], mark[N], included[N];

void artic_points(int u) {
    dfs_low[u] = dfs_num[u] = dfsCont++;
    for (int v : aux[u]) {
        if (!dfs_num[v] && !visited[v]) {
            dfs_parent[v] = u;
            if (u == dfsRoot) rootChildren++;

            artic_points(v);

            if (dfs_low[v] >= dfs_num[u])
                art_point[u] = true;
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (dfs_num[v] && v != dfs_parent[u])
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

pair < vector < int >, int > used[N];

void dfs(int u) {
    mark[u] = true;
    used[cont].first.push_back(u);

    for (int v : aux[u]) {
        if (!mark[v])
            dfs(v);
        else if (art_point[v]) {
            int l = used[cont].second;
            while (l > 10000) l -= 10000;

            if (l == 0) used[cont].second = v;
            else if (v != l) used[cont].second = -1;
            else used[cont].second += 10000;
        }
    }
}

bool cmp(pair < vector < int >, int > a, pair < vector < int >, int > b) {
	return a.second > b.second;
}

#define source 115
#define sink 116

int main() {
	scanf("%d", &t);
	for (int tc = 0; tc < t; tc++) {

		for (int i = 0; i < N; i++) {
			aux[i].clear();
			visited[i] = mark[i] = included[i] = false;
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

        while (1) {
            int left = n;
            for (int i = 1; i <= n; i++) left -= visited[i];
            if (left == 0) break;

            for (int i = 0; i < N; i++) {
				mark[i] = art_point[i] | visited[i];
                used[i].first.clear();
                used[i].second = 0;
			}

            cont = 0;
            for (int i = 1; i <= n; i++)
                if (!mark[i]) {
                    dfs(i);
                    cont++;
                }

            sort(used, used+cont, cmp);

            for (int i = 0; i < cont; i++) {
                if (used[i].second < 0) break;

                if (used[i].first.size() + (used[i].second > 0) < 3) {
                    for (int v : used[i].first) {
                        if (!included[v])
                            regions.push_back(supply[v]);
                        if (!art_point[v])
                            visited[v] = true;
                    }
                    continue;
                }

                int sum = 0;
                for (int v : used[i].first) {
                    sum += supply[v];
                    visited[v] = true;
                }

                bool cycle = used[i].second > 10000;
                while (used[i].second > 10000) used[i].second -= 10000;

                if (cycle) { sum += supply[used[i].second]; included[used[i].second] = true; }
                regions.push_back(sum);
            }

            for (int i = 1; i <= n; i++)
                dfs_num[i] = dfs_low[i] = dfs_parent[i] = art_point[i] = 0;

            dfsCont = 1;
            for (int i = 1; i <= n; i++)
                if (!dfs_num[i]) {
                    dfsRoot = i; rootChildren = 0; artic_points(i);
                    art_point[dfsRoot] = (rootChildren > 1);
                }
        }

        printf("%d\n", regions[0]);
        int maxi = 0;
        for (int i = 1; i <= b; i++)
            maxi = max(maxi, energy[i]);

        printf("%d\n", maxi);

        if (regions.size() > b) printf("Buzz Mission %d: %d No\n", tc+1, regions.size());
        else {
            int ini = 0, fim = 100000;
            while (ini <= fim) {
                int meio = (ini + fim) / 2;

                for (int i = 0; i < N; i++)
                    graph[i].clear();

                for (int i = 1; i <= b; i++)
                    addEdge(source, i, 1);
                for (int i = 0; i < regions.size(); i++)
                    addEdge(i+60, sink, 1);
                for (int i = 1; i <= b; i++)
                    for (int j = 0; j < regions.size(); j++)
                        if (abs(regions[j]-energy[i]) <= meio)
                            addEdge(i, j+60, 1);

                printf("%d\n", meio);

                if (flow(source, sink) < regions.size()) ini = meio + 1;
                else fim = meio - 1;
            }

            printf("Buzz Mission %d: %d %d\n", tc+1, regions.size(), ini);
        }
	}

	return 0;
}

/*
10000
5 6 3
1 6 7 2 6
1 8 6
1 2
2 3
3 1
3 4
4 5
5 3

10 12 6
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1
1 2
2 3
3 1
3 4
4 5
5 3
4 6
3 7
3 8
7 9
8 9
9 10
*/

