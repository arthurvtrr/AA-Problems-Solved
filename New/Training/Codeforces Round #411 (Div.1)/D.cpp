#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, m, q, x, y, comp[100100], siz[100100];
vector < int > graph[100100], aux;
bool visited[100100];
map < int, int > dist[2];
long long best[100100], diam[100100];
vector < long long > maxpath[100100], acum[100100];
map < pii, double > ans;

void dfs(int u, int c) {
    visited[u] = true;
    comp[u] = c;
    siz[c]++;
    for (int v : graph[u])
        if (!visited[v])
            dfs(v, c);
}

int bfs(int ini, int t) {
    dist[t].clear();
    queue < int > fila;
    dist[t][ini] = 0;
    fila.push(ini);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();
        visited[u] = true;
        if (t) aux.push_back(u);

        for (int v : graph[u])
            if (!dist[t].count(v)) {
                dist[t][v] = dist[t][u] + 1;
                fila.push(v);
            }
    }

    int ret = ini;
    for (map <int, int>::iterator it = dist[t].begin(); it != dist[t].end(); it++)
        if (dist[t][ret] < it->second)
            ret = it->first;
    return ret;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int cmp = 1;
    for (int i = 1; i <= n; i++)
        if (!visited[i]) {
            dfs(i, cmp);
            cmp++;
        }

    for (int i = 1; i <= n; i++) visited[i] = false;

    for (int i = 1; i <= n; i++)
        if (!visited[i]) {
            int a = bfs(i, 0);
            int b = bfs(a, 0);
            bfs(b, 1);

            for (int v : aux) {
                best[v] = max(dist[0][v], dist[1][v]);
                diam[comp[i]] = max(diam[comp[i]], (long long)dist[0][v]);
            }
            aux.clear();
        }

    for (int i = 1; i <= n; i++)
        maxpath[comp[i]].push_back(best[i]);
    for (int i = 1; i < cmp; i++) {
        sort(maxpath[i].begin(), maxpath[i].end());
        for (int j = 0; j < siz[i]; j++)
            acum[i].push_back(maxpath[i][j]);
    }

    for (int i = 1; i < cmp; i++)
        for (int j = 1; j < acum[i].size(); j++)
            acum[i][j] += acum[i][j-1];

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &x, &y);
        if (siz[comp[x]] > siz[comp[y]]) swap(x, y);

        if (comp[x] == comp[y]) printf("-1\n");
        else if (ans.count(pii(comp[x], comp[y]))) printf("%.10f\n", ans[pii(comp[x], comp[y])]);
        else {
            double sol = 0.0;
            for (int j = 0; j < siz[comp[x]]; j++) {
                long long maxd = max(diam[comp[x]], diam[comp[y]]);

                int ini = 0, fim = siz[comp[y]]-1;
                while (ini <= fim) {
                    int mid = (ini + fim) / 2;
                    if (maxpath[comp[x]][j] + maxpath[comp[y]][mid] + 1 <= maxd) ini = mid+1;
                    else fim = mid-1;
                }
                double tmp = 0.0;
                tmp += (fim+1) * maxd;
                //printf("1 - %f\n", tmp);
                tmp += (siz[comp[y]]-1-fim) * (maxpath[comp[x]][j] + 1);
                //printf("2 - %f\n", tmp);
                //for (int k = 0; k < acum[comp[y]].size(); k++)
                //    printf(" %lld", acum[comp[y]][k]);
                //printf("\n");
                tmp += acum[comp[y]].back() - (fim >= 0? acum[comp[y]][fim] : 0);
                //printf("3 - %f\n", tmp);
                sol += tmp / siz[comp[x]] / siz[comp[y]];
            }
            ans[pii(comp[x], comp[y])] = sol;
            printf("%.10f\n", sol);
        }
    }

    return 0;
}
