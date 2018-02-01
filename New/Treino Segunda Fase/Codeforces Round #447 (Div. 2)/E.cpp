#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define N 1001000
#define pii pair < int, int >

int n, m, s, cnt, c, cmp[N], dfs_num[N], dfs_low[N], visited[N];
vector < int > graph[N], aux;
vector < pii > ng[N];
ll val[N], quant[N];

struct edge {
	int x, y, z;
} edges[N];

void tarjan(int u) {
	dfs_low[u] = dfs_num[u] = cnt++;
	aux.push_back(u);
	visited[u] = 1;
	for (int v : graph[u]) {
		if (!dfs_num[v])
			tarjan(v);
		if (visited[v])
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
	}

	if (dfs_low[u] == dfs_num[u]) {
		while (1) {
			int v = aux.back(); aux.pop_back(); visited[v] = 0;
			cmp[v] = c;
			if (u == v) break;
		}
		c++;
	}
}

ll dp[N];

ll solve(int u) {
	if (dp[u] != -1) return dp[u];

	ll ret = 0;
	for (pii v : ng[u])
		ret = max(ret, solve(v.first) + v.second + val[v.first]);
	return dp[u] = ret;
}

bool cmp1(pii a, pii b) {
   return a.second > b.second;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].z);
		graph[edges[i].x].push_back(edges[i].y);
	}

	scanf("%d", &s);

	cnt = 1; c = 1;
	for (int i = 1; i <= n; i++)
		if (!dfs_num[i])
			tarjan(i);

	for (int i = 1; i < 20010; i++)
		quant[i] = i*(i+1)/2;

	for (int i = 1; i < 20010; i++)
		quant[i] += quant[i-1];

    for (int i = 0; i < m; i++) {
        edges[i].x = cmp[edges[i].x];
        edges[i].y = cmp[edges[i].y];
    }

    for (int i = 0; i < m; i++) {
        if (edges[i].x == edges[i].y) continue;
        ng[edges[i].x].push_back(pii(edges[i].y, edges[i].z));
    }

    for (int i = 1; i < c; i++)
        sort(ng[i].begin(), ng[i].end(), cmp1);

	for (int i = 0; i < m; i++) {
		int ca = edges[i].x, cb = edges[i].y;
		if (ca == cb) {
            ll ini = 1, fim = 20020;
			while (ini <= fim) {
				ll meio = (ini + fim) / 2;
				if (meio*(meio+1)/2 <= edges[i].z) ini = meio+1;
				else fim = meio-1;
			}
			val[ca] += (fim+1)*edges[i].z - quant[fim];
		}
	}

	memset(dp, -1, sizeof dp);

	printf("%lld\n", solve(cmp[s]) + val[cmp[s]]);

	return 0;
}
