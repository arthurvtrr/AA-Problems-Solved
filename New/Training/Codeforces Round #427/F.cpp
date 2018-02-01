#include <bits/stdc++.h>

using namespace std;

int n;

struct edge {
    int x, y, z;
} edges[200200];

bool cmp(edge a, edge b) {
    return a.z < b.z;
}

struct subset {
    int parent, rank;
} subsets[200200];

int find(int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets[i].parent);
    return subsets[i].parent;
}

void Union(int x, int y) {
    int xroot = find(x), yroot = find(y);

    if (subsets[xroot].rank < subsets[yroot].rank) subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank) subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

#define ll long long
#define pll pair < ll, ll >
#define INF 1000000000000000LL

vector < pll > graph[200200];

ll dist[2][200200];

int bfs(int ini, int t) {
    for (int i = 0; i < 200200; i++)
        dist[t][i] = INF;
    priority_queue < pll > fila;
    dist[t][ini] = 0;
    fila.push(pll(0, ini));

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();

        for (pll v : graph[u]) {
            if (dist[t][v.first] > dist[t][u] + v.second) {
                dist[t][v.first] = dist[t][u] + v.second;
                fila.push(pll(-dist[t][v.first], v.first));
            }
        }
    }

    int ret = 1;
    for (int i = 2; i <= n; i++)
        if (dist[t][ret] < dist[t][i])
            ret = i;

    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].z);
    sort(edges, edges+n, cmp);

    for (int i = 1; i <= n; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 1;
    }

    for (int i = 0; i < n; i++) {
        int a = find(edges[i].x), b = find(edges[i].y);
        if (a != b) {
            Union(a, b);
            graph[edges[i].x].push_back(pll(edges[i].y, edges[i].z));
            graph[edges[i].y].push_back(pll(edges[i].x, edges[i].z));
        }
    }

    int x = bfs(1, 0);
    bfs(x, 1);

    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dist[1][i]);
    printf("%lld\n", ans);

    return 0;
}
