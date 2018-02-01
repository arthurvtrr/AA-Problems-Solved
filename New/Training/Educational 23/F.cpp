#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define N 330000

struct Node {
    ll val = 0, acum = 0, siz = 0;

    void atualize(int x) {
        if (x == 0) return;

        if (x < 3) {
            acum = x;
            val = (x == 2? 0 : x) * siz;
        }
        else {
            acum = 3 - acum;
            if (acum == 3 || acum == 0) val = siz - val;
            else val = (acum == 2? 0 : acum) * siz;
        }
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum);
        right.atualize(acum);
        acum = 0;
    }

    void _merge(Node& left, Node& right) {
        val = left.val + right.val;
    }

} seg[4*N];

void build(int id, int ini, int fim) {
    seg[id].siz = fim - ini + 1;
    if (ini == fim) return;

    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);
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

int query(int id, int ini, int fim) {
    if (ini == fim) return ini;

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    if (seg[2*id].val != seg[2*id].siz) return query(2*id, ini, meio);
    return query(2*id+1, meio+1, fim);
}

int n;
ll t[N], l[N], r[N];
set < ll > vals;
map < ll, ll > pos, inv;

int main() {
    build(1, 1, N);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &t[i], &l[i], &r[i]);
        vals.insert(l[i]);
        vals.insert(r[i]);
        vals.insert(r[i]+1);
    }
    vals.insert(1);

    int cnt = 1;
    for (auto v : vals) {
        pos[v] = cnt;
        inv[cnt++] = v;
    }

    for (int i = 0; i < n; i++) {
        l[i] = pos[l[i]];
        r[i] = pos[r[i]];
    }

    for (int i = 0; i < n; i++) {
        if (t[i] == 1) update(1, 1, N, l[i], r[i], 1);
        else if (t[i] == 2) update(1, 1, N, l[i], r[i], 2);
        else update(1, 1, N, l[i], r[i], 3);

        printf("%lld\n", inv[query(1, 1, N)]);
    }

    return 0;
}
