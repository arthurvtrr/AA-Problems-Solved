#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

int t, n, m, x, y;

vector < int > graph[20020], aux;
bool visited[20020];
int counter, scc, dfs_num[20020], dfs_low[20020], incEdges[20020], outEdges[20020], cp[20020];

void dfs(int u) {
    dfs_low[u] = dfs_num[u] = counter++;
    aux.push_back(u);
    visited[u] = true;

    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];

        if (!dfs_num[v])
            dfs(v);
        if (visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {
        while (1) {
            int v = aux.back();
            aux.pop_back();
            visited[v] = false;
            cp[v] = scc;

            if (u == v) break;
        }
        scc++;
    }
}

int main() {
    scanf("%d", &t);

    while (t--) {
        for (int i = 0; i < 20020; i++) {
            graph[i].clear();
            visited[i] = false;
            dfs_num[i] = dfs_low[i] = incEdges[i] = outEdges[i] = cp[i] = 0;
        }
        aux.clear();

        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            graph[x].push_back(y);
        }

        counter = scc = 1;
        for (int i = 1; i <= n; i++)
            if (!dfs_num[i])
                dfs(i);

        for (int i = 1; i <= n; i++)
            for (int j = 0; j < graph[i].size(); j++)
                if (cp[i] != cp[graph[i][j]]) {
                    incEdges[cp[graph[i][j]]]++;
                    outEdges[cp[i]]++;
                }

        int oute = 0, ince = 0;

        for (int i = 1; i < scc; i++) {
            if (outEdges[i] == 0) oute++;
            if (incEdges[i] == 0) ince++;
        }

        if (scc == 2) printf("0\n");
        else printf("%d\n", max(oute, ince));
    }
    return 0;
}
