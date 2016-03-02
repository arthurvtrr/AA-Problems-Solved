#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define N 110000

struct Node {
    int depth;
    int ini_path;
    int weight;
    int parent;
    int pos;
} nodes[N];

int seg[4*N], nums[N];

bool cmp(int a, int b) {
    return nodes[a].depth < nodes[b].depth;
}

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = nums[ini];
        return;
    }

    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    seg[id] = max(seg[2*id], seg[2*id+1]);
}

void update(int id, int ini, int fim, int pos, int val) {
    if (ini == fim) {
        seg[id] = val;
        return;
    }

    int meio = (ini + fim) / 2;

    if (pos <= meio) update(2*id, ini, meio, pos, val);
    else update(2*id+1, meio+1, fim, pos, val);

    seg[id] = max(seg[2*id], seg[2*id+1]);
}

int query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id];

    int meio = (ini + fim) / 2;

    return max(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

bool visited[N];
vector < int > graph[N], paths[N];

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

int get_max(int a, int b) {
    int aux = 0;
    while (nodes[a].ini_path != nodes[b].ini_path) {
        aux = max(aux, query(1, 1, n, nodes[nodes[a].ini_path].pos, nodes[a].pos));
        a = nodes[nodes[a].ini_path].parent;
    }
    aux = max(aux, query(1, 1, n, nodes[b].pos+1, nodes[a].pos));
    return aux;
}

int main() {
    //get input and construct graph

    dfs1(1, 1);

    for (int i = 0; i < N; i++)
        visited[i] = false;

    dfs2(1, 1);

    //calculate the position that each node needs to be on segment tree
    int cont = 1;
    for (int i = 1; i < N; i++) {
        sort(paths[i].begin(), paths[i].end(), cmp);
        for (int j = 0; j < paths[i].size(); j++) {
            nodes[paths[i][j]].pos = cont;
            cont++;
        }
    }

    for (int i = 1; i <= n; i++)
        nums[nodes[i].pos] = nodes[i].cost;

    build(1, 1, n);

    //queries

    return 0;
}
