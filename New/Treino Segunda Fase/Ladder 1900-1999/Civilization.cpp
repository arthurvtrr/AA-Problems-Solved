#include <bits/stdc++.h>

using namespace std;

int n, m, q, x, y, z, siz[300300];
vector < int > graph[300300];

struct subset {
    int parent, rank;
} subsets[300300];

int Find(int x) {
    if (subsets[x].parent != x) subsets[x].parent = Find(subsets[x].parent);
    return subsets[x].parent;
}

void Union(int x, int y) {
    int rx = Find(x), ry = Find(y);
    if (subsets[rx].rank > subsets[ry].rank)
        subsets[ry].parent = rx;
    else if (subsets[rx].rank < subsets[ry].rank)
        subsets[rx].parent = ry;
    else {
        subsets[ry].parent = rx;
        subsets[rx].rank++;
    }
}

bool visited[300300];
vector < int > vis;
int dist[300300], best;

void dfs(int u, int d) {
    visited[u] = true;
    vis.push_back(u);
    dist[u] = d;

    if (d > dist[best]) best = u;

    for (int v : graph[u])
        if (!visited[v])
            dfs(v, d+1);
}

int main() {
    scanf("%d %d %d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 1;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
        Union(x, y);
    }

    for (int i = 1; i <= n; i++)
        if (!visited[i]) {
            best = i;
            dfs(i, 0);
            for (int v : vis) {
                visited[v] = false;
                dist[v] = 0;
            }
            vis.clear();

            dfs(best, 0);
            vis.clear();
            siz[Find(i)] = dist[best];
        }

    for (int i = 0; i < q; i++) {
        scanf("%d", &x);
        if (x == 1) {
            scanf("%d", &y);
            printf("%d\n", siz[Find(y)]);
        }
        else {
            scanf("%d %d", &y, &z);
            if (Find(y) == Find(z)) continue;

            int a = siz[Find(y)], b = siz[Find(z)];
            Union(y, z);
            siz[Find(y)] = max({a, b, (a+1)/2 + (b+1)/2 + 1});
        }
    }

    return 0;
}
