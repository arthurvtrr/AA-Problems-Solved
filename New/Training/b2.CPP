#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000
#define N 120
#define pii pair < int, int >

int n_elements = N;
int visitado[N], pai[N], dist[N], cost[N][N], cap[N][N], r_cost[N][N];

void addEdge(int a, int b, int _cap, int c) {
    cost[a][b] = c;
    cap[a][b] = _cap;
    r_cost[a][b] = c;
    cost[b][a] = -c;
    r_cost[b][a] = -c;
}

int dijkstra() {
    for (int i = 0; i < n_elements; i++) {
        visitado[i] = 0; pai[i] = -1; dist[i] = INF;
    }
    dist[0] = 0;
    int cur = 0, last_cur = -1;
    while (1) {
        if (last_cur == cur) break;
        visitado[cur] = 1;
        int min_dist = INF, new_cur = cur;
        for (int i = 0; i < n_elements; i++) {
            if (visitado[i] == 1) continue;
            if (cap[cur][i] > 0 && dist[i] > cost[cur][i] + dist[cur])
                dist[i] = cost[cur][i] + dist[cur], pai[i] = cur;
            if (dist[i] < min_dist) {
                min_dist = dist[i];
                new_cur = i;
            }
        }
        last_cur = cur;
        cur = new_cur;
    }
    if (pai[n_elements-1] == -1) return 0;
    return 1;
}

void update_potencials() {
    for (int i = 0; i < n_elements; i++)
        for (int j = 0; j < n_elements; j++)
            if (dist[i] != INF && dist[j] != INF)
                cost[i][j] += dist[i] - dist[j];
}

int bellman_ford() {
    for (int i = 0; i < n_elements; i++) dist[i] = INF;
    dist[0] = 0;
    bool changed = false;
    for (int i = 0; i < n_elements; i++) {
        changed = false;
        for (int j = 0; j < n_elements; j++) {
            if (dist[j] == INF) continue;
            for (int z = 0; z < n_elements; z++) {
                if (cap[j][z] == 0) continue;
                if (dist[z] > dist[j] + cost[j][z]) {
                    dist[z] = dist[j] + cost[j][z];
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }

    return !changed;
}

pii MCMF() {
    if (!bellman_ford()) while(1);
    update_potencials();
    int tot = 0;
    int m_flow = 0;
    while (dijkstra()) {
        int x = n_elements - 1;
        int r_max = INF;
        while (pai[x] != -1) {
            int p = pai[x];
            r_max = min(r_max, cap[p][x]);
            x = p;
        }
        x = n_elements-1;
        while (pai[x] != -1) {
            int p = pai[x];
            cap[p][x] -= r_max, cap[x][p] += r_max;
            tot = max(tot, r_cost[p][x]*r_max), x = p;
        }
        m_flow += r_max;
        update_potencials();
    }
    return make_pair(m_flow, tot);
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
			aux[i].clear();
			visited[i] = false;
			dfs_num[i] = dfs_low[i] = dfs_parent[i] = art_point[i] = 0;
            for (int j = 0; j < N; j++)
                cost[i][j] = cap[i][j] = r_cost[i][j] = 0;
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

            pii ans = MCMF();
            printf("Buzz Mission %d: %d %d\n", tc+1, regions.size(), ans.second);
        }
	}

	return 0;
}
