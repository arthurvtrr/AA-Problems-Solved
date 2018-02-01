#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

#define N 100100

struct Node {
    int depth;
    int ini_path;
    int weight;
    int parent;
    int pos;
    int num;
} nodes[N];

int nums[N];

bool cmp(int a, int b) {
    return nodes[a].depth < nodes[b].depth;
}

int n, m, a, b, c;
bool visited[N];
vector < int > graph[N], paths[N];
set < int > local[N];

void dfs1(int u, int dep) {
    visited[u] = true;
    nodes[u].depth = dep;
    nodes[u].weight = 1;
    for (int v : graph[u])
        if (!visited[v]) {
            nodes[v].parent = u;
            dfs1(v, dep+1);
            nodes[u].weight += nodes[v].weight;
        }
}

void dfs2(int u, int id) {
    visited[u] = true;
    paths[id].push_back(u);
    nodes[u].ini_path = id;

    for (int v : graph[u])
        if (!visited[v]) {
            if (nodes[v].weight*2 < nodes[u].weight)
                dfs2(v, v);
            else
                dfs2(v, id);
        }
}

int lca(int a, int b) {
    while (nodes[a].ini_path != nodes[b].ini_path) {
        if (nodes[nodes[a].ini_path].depth >= nodes[nodes[b].ini_path].depth)
            a = nodes[nodes[a].ini_path].parent;
        else
            b = nodes[nodes[b].ini_path].parent;
    }
    return (nodes[a].depth < nodes[b].depth? a : b);
}

bool query(int a, int b, int c) {
    bool found = false;
    int x;

    while (nodes[a].ini_path != nodes[b].ini_path) {
        x = *local[c].lower_bound(nodes[nodes[a].ini_path].pos);
        if (x >= nodes[nodes[a].ini_path].pos && x <= nodes[a].pos)
            found = true;
        a = nodes[nodes[a].ini_path].parent;
    }

    x = *local[c].lower_bound(nodes[b].pos);
    if (x <= nodes[a].pos && x >= nodes[b].pos)
        found = true;

    return found;
}

void clean() {
    for (int i = 0; i < N; i++) {
        nodes[i].depth = 0;
        nodes[i].parent = 0;
        nodes[i].ini_path = 0;
        nodes[i].weight = 0;
        nodes[i].num = 0;
        nodes[i].pos = 0;

        visited[i] = false;
        nums[i] = 0;
        graph[i].clear();
        paths[i].clear();
        local[i].clear();
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%d", &m);

        clean();

        for (int i = 1; i <= n; i++) {
            scanf("%d", &a);
            nodes[i].num = a;
        }

        for (int i = 0; i < n-1; i++) {
            scanf("%d %d", &a, &b);
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        dfs1(1, 1);

        for (int i = 0; i < N; i++)
            visited[i] = false;

        dfs2(1, 1);

        int cont = 1;
        for (int i = 1; i < N; i++) {
            sort(paths[i].begin(), paths[i].end(), cmp);
            for (int j = 0; j < paths[i].size(); j++) {
                nodes[paths[i][j]].pos = cont;
                cont++;
            }
        }

        for (int i = 1; i <= n; i++) {
            nums[nodes[i].pos] = nodes[i].num;
            local[nodes[i].num].insert(nodes[i].pos);
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &c);

            int Lca = lca(a, b);
            if (query(a, Lca, c) || query(b, Lca, c)) printf("Find\n");
            else printf("NotFind\n");
        }
        printf("\n");
    }
    return 0;
}
