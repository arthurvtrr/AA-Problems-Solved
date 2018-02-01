#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, c;
vector < int > ct[110], confs[505];
vector < pii > graph[110];
int dg[110], cnt[110][110], bridge[110][110];

bool visited[110];

void dfs(int u) {
    visited[u] = true;
    for (pii v : graph[u])
        if (!visited[v.first])
            dfs(v.first);
}

int counter, dfs_num[110], dfs_low[110], dfs_parent[110];

void bridges(int u) {
    dfs_low[u] = dfs_num[u] = counter++;
    for (pii v : graph[u]) {
        if (!dfs_num[v.first]) {
            dfs_parent[v.first] = u;
            bridges(v.first);

            if (dfs_low[v.first] > dfs_num[u] && cnt[u][v.first] == 1)
                bridge[u][v.first] = bridge[v.first][u] = 1;
            dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
        }
        else if (v.first != dfs_parent[u])
            dfs_low[u] = min(dfs_low[u], dfs_num[v.first]);
    }
}

int main() {
    while (1) {
        scanf("%d %d", &n, &c);
        if (n + c == 0) break;

        for (int i = 0; i < c; i++) {
            int x, y;
            scanf("%d", &x);
            for (int j = 0; j < x; j++) {
                scanf("%d", &y);
                ct[i].push_back(y);
                confs[y].push_back(i);
            }
        }

        for (int i = 0; i < n; i++) {
            if (confs[i].size() == 1) {
                dg[confs[i][0]] += 2;
                graph[confs[i][0]].push_back(pii(confs[i][0], i));
            }
            else {
                dg[confs[i][0]]++; dg[confs[i][1]]++;
                graph[confs[i][0]].push_back(pii(confs[i][1], i));
                graph[confs[i][1]].push_back(pii(confs[i][0], i));
                cnt[confs[i][0]][confs[i][1]]++;
                cnt[confs[i][1]][confs[i][0]]++;
            }
        }

        bool con = true;
        for (int i = 0; i < c; i++)
            if (!ct[i].empty()) {
                dfs(i);
                break;
            }

        for (int i = 0; i < c; i++)
            if (!ct[i].empty() && !visited[i])
                con = false;

        vector < int > odd;
        for (int i = 0; i < c; i++)
            if (dg[i] % 2)
                odd.push_back(i);

        int ans = -1;

        if (con && odd.size() == 2) {
            counter = 1;
            for (int i = 0; i < c; i++)
                if (!dfs_num[i])
                    bridges(i);

            ans = n-1;
            for (int v : odd)
                for (int i = 0; i < graph[v].size(); i++)
                    if (graph[v].size() == 1 || !bridge[v][graph[v][i].first])
                        ans = min(ans, graph[v][i].second);
        }
        if (con && odd.size() == 0) ans = 0;

        printf("%d\n", ans);

        for (int i = 0; i < c; i++) {
            ct[i].clear();
            graph[i].clear();
            dg[i] = visited[i] = dfs_num[i] = dfs_low[i] = dfs_parent[i] = 0;
        }

        for (int i = 0; i < n; i++)
            if (confs[i].size() != 1) {
                cnt[confs[i][0]][confs[i][1]] = 0;
                cnt[confs[i][1]][confs[i][0]] = 0;
                bridge[confs[i][0]][confs[i][1]] = 0;
                bridge[confs[i][1]][confs[i][0]] = 0;
            }

        for (int i = 0; i < n; i++)
            confs[i].clear();
    }
    return 0;
}
