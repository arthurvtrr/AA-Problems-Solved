#include <bits/stdc++.h>

using namespace std;

#define N 100100
#define INF 10000000

int n, k, bit[N];

void update(int pos, int val) {
    while (pos < N) {
        bit[pos] += val;
        pos += pos & -pos;
    }
}

int query(int pos) {
    int ret = 0;
    while (pos) {
        ret += bit[pos];
        pos -= pos & -pos;
    }
    return ret;
}

struct el {
    int num, bad;
} els[N];

bool cmp(el a, el b) {
    return a.num < b.num;
}

struct Node {
    int val, b, pos, acum, siz;

    void atualize(int x) {
        val += x;
        acum += x;
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum);
        right.atualize(acum);
        acum = 0;
    }

    void _merge(Node& left, Node& right) {
        if (left.val <= right.val) {
            val = left.val;
            b = left.b;
            pos = left.pos;
        }
        else {
            val = right.val;
            b = right.b;
            pos = right.pos;
        }
    }
} seg[4*N];

void build(int id, int ini, int fim) {
    seg[id].siz = fim - ini + 1;

    if (ini == fim) {
        seg[id].val = els[ini].bad;
        seg[id].b = els[ini].num;
        seg[id].pos = ini;
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

Node query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return (Node) {INF*100, 0, 0, 0, 0};
    if (ini >= start && fim <= end)
        return seg[id];

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);
    Node a = query(2*id, ini, meio, start, end);
    Node b = query(2*id+1, meio+1, fim, start, end);

    if (a.val <= b.val) return a;
    return b;
}

int fps(int x) {
    int ini = 1, fim = n;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (els[meio].num < x) ini = meio+1;
        else fim = meio-1;
    }
    return ini;
}

int lpos(int x) {
    int ini = 1, fim = n;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (els[meio].num <= x) ini = meio+1;
        else fim = meio-1;
    }
    return fim;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &els[i].num);

    for (int i = 1; i <= n; i++) {
        update(els[i].num, 1);
        els[i].bad = query(N-1) - query(min(N-1, els[i].num + k)) + query(max(0, els[i].num - k - 1));
        printf("%d\n", els[i].bad);
    }

    sort(els+1, els+n+1, cmp);
    build(1, 1, n);

    vector < int > ans;
    for (int i = 0; i < n; i++) {
        Node x = query(1, 1, n, 1, n);
        ans.push_back(x.b);

        int a = fps(x.b + k + 1), b = lpos(x.b - k - 1);
        if (b >= 1) update(1, 1, n, 1, b, -1);
        if (a <= n) update(1, 1, n, a, n, -1);

        update(1, 1, n, x.pos, x.pos, INF);
    }

    for (int i = 0; i < ans.size(); i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
