#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <set>

using namespace std;

int n, m, k, x, y;
bool special[1010], visited[1010], edge[1010][1010];

vector < int > graph[1010], cmp[1010];

void dfs(int u, int c) {
    visited[u] = true;
    cmp[c].push_back(u);

    for (int v : graph[u])
        if (!visited[v])
            dfs(v, c);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &x);
        special[x] = true;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
        edge[x][y] = edge[y][x] = true;
    }

    int comp = 1;
    for (int i = 1; i <= n; i++)
        if (!visited[i] && special[i]) {
            dfs(i, comp);
            comp++;
        }

    vector < int > left;
    for (int i = 1; i <= n; i++)
        if (!visited[i]) left.push_back(i);

    int quant = 0;
    for (int i = 0; i < left.size(); i++)
        for (int j = i+1; j < left.size(); j++)
            if (edge[left[i]][left[j]]) quant++;

    int sol = 0, chosen = 0;

    for (int i = 1; i < comp; i++) {
        int siz = cmp[i].size();
        int edges = 0;
        for (int j = 0; j < cmp[i].size(); j++)
            for (int l = j+1; l < cmp[i].size(); l++)
                if (edge[cmp[i][j]][cmp[i][l]])
                    edges++;

        int total = (left.size() + siz) * (left.size() + siz - 1) / 2;

        if (sol < total - quant - edges) {
            sol = total - quant - edges;
            chosen = i;
        }
    }

    for (int i = 1; i < comp; i++)
        if (i != chosen) {
            int siz = cmp[i].size();
            int edges = 0;
            for (int j = 0; j < cmp[i].size(); j++)
                for (int l = j+1; l < cmp[i].size(); l++)
                    if (edge[cmp[i][j]][cmp[i][l]])
                        edges++;

            sol += siz * (siz-1) / 2 - edges;
        }

    printf("%d\n", sol);

    return 0;
}
