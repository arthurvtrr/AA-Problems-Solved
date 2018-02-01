#include <bits/stdc++.h>

using namespace std;

#define N 500500
#define pii pair < int, int >

int n, x, y, q, cont, parent[N];
pii interval[N];
vector < int > graph[N];

void dfs(int u, int p) {
    interval[u].first = cont++;
    parent[u] = p;
    for (int v : graph[u])
        if (v != p)
            dfs(v, u);
    interval[u].second = cont-1;
}

struct Node {
    int val, siz, acum;

    void atualize(int x) {
        if (x == -1) { val = 0; acum = -1; }
        else if (x == 1) { val = siz; acum = 1; }
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum);
        right.atualize(acum);
        acum = 0;
    }

    void _merge(Node& left, Node& right) {
        val = left.val + right.val;
        siz = left.siz + right.siz;
    }

} seg[4*N];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id].val = seg[id].siz = 1;
        return;
    }

    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

void update(int id, int ini, int fim, int start, int end, int val) {
    if (start > fim || end < ini)
        return;
    if (ini >= start && fim <= end) {
        seg[id].atualize(val);
        return;
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    update(2*id, ini, meio, start, end, val);
    update(2*id+1, meio+1, fim, start, end, val);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

int query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id].val;

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    return query(2*id, ini, meio, start, end) + query(2*id+1, meio+1, fim, start, end);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    cont = 1;
    dfs(1, 0);
    build(1, 1, n);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &x, &y);

        if (x == 1) {
            int aux = query(1, 1, n, interval[y].first, interval[y].second);
            if (aux > 0 && y != 1) update(1, 1, n, interval[parent[y]].first, interval[parent[y]].first, 1);
            update(1, 1, n, interval[y].first, interval[y].second, -1);
        }
        else if (x == 2) {
            update(1, 1, n, interval[y].first, interval[y].first, 1);
        }
        else {
            int aux = query(1, 1, n, interval[y].first, interval[y].second);
            printf("%d\n", aux == 0);
        }
    }

    return 0;
}
