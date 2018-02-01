#include <bits/stdc++.h>

using namespace std;

int n, x, y, maxi;
vector < int > graph[100100];

int dfsCounter, dfsRoot, rootChildren;
int dfs_num[100100], dfs_low[100100], dfs_parent[100100], artic_point[100100];

void calc_points(int u) {
    dfs_low[u] = dfs_num[u] = dfsCounter++;

    for (int v : graph[u]) {
        if (!dfs_num[v]) {
            dfs_parent[v] = u;
            if (u == dfsRoot) rootChildren++;

            calc_points(v);

            if (dfs_low[v] >= dfs_num[u])
                artic_point[u] = true;
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (v != dfs_parent[u])
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

bool visited[100100];
int siz;
set < int > reached;

void dfs(int u) {
    visited[u] = true;
    siz++;
    for (int v : graph[u]) {
        if (artic_point[v]) reached.insert(v);
        else if (!visited[v]) dfs(v);
    }
}

int main() {
    int t = 1;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        maxi = 0;
        for (int i = 0; i < 100100; i++)
            graph[i].clear();

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            graph[x].push_back(y);
            graph[y].push_back(x);
            maxi = max(maxi, max(x, y));
        }

        dfsCounter = 1;
        for (int i = 1; i <= maxi; i++)
            dfs_num[i] = dfs_low[i] = dfs_parent[i] = artic_point[i] = visited[i] = 0;

        for (int i = 1; i <= maxi; i++)
            if (!dfs_num[i]) {
                dfsRoot = i;
                rootChildren = 0;
                calc_points(i);
                artic_point[dfsRoot] = rootChildren > 1;
            }

        bool found = false;
        for (int i = 1; i <= maxi; i++)
            if (artic_point[i])
                visited[i] = found = true;

        if (maxi == 1) {
            printf("Case %d: 0 0\n", t++);
        }
        else if (!found) {
            long long x = maxi;
            printf("Case %d: 2 %lld\n", t++, x * (x-1) / 2);
        }
        else {
            long long quant = 0, ways = 1;
            for (int i = 1; i <= maxi; i++)
                if (!visited[i]) {
                    siz = 0;
                    reached.clear();
                    dfs(i);
                    if (reached.size() == 1) {
                        quant++;
                        ways *= siz;
                    }
                }

            printf("Case %d: %lld %lld\n", t++, quant, ways);
        }
    }

    return 0;
}
