#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000000
#define N 100100

struct Node {
    int val[45] = {0};
    int acum = 0;

    void atualize(int x) {
        for (int i = 44; i > x; i--) val[i] = val[i-x];
        for (int i = 0; i <= min(x, 44); i++) val[i] = 0;
        acum += x;
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum);
        right.atualize(acum);
        acum = 0;
    }

    void _merge(Node& left, Node& right) {
        for (int i = 1; i < 45; i++)
            val[i] = left.val[i] + right.val[i];
    }

} seg[4*N];

int nums[N];
ll fat[200];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        if (nums[ini] < 45)
            seg[id].val[nums[ini]] = 1;
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

void update(int id, int ini, int fim, int pos, int v) {
    if (ini == fim) {
        for (int i = 0; i < 45; i++)
            seg[id].val[i] = 0;
        seg[id].val[v] = 1;
        return;
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    if (pos <= meio) update(2*id, ini, meio, pos, v);
    else update(2*id+1, meio+1, fim, pos, v);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

ll query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end) {
        ll ret = 0;
        for (int i = 1; i < 45; i++) {
            ret += fat[i] * seg[id].val[i];
            ret %= MOD;
        }
        return ret;
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    return (query(2*id, ini, meio, start, end) + query(2*id+1, meio+1, fim, start, end)) % MOD;
}

int n, m, a, b, c;

int main() {
    fat[0] = 1;
    for (int i = 1; i < 200; i++) {
        fat[i] = fat[i-1] * i;
        fat[i] %= MOD;
    }

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);
    build(1, 1, n);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        if (a == 1) {
            update(1, 1, n, b, c, 1);
        }
        else if (a == 2) {
            printf("%lld\n", query(1, 1, n, b, c));
        }
        else {
            if (c < 45) update(1, 1, n, b, c);
            else update(1, 1, n, b, 0);
        }
    }

    return 0;
}
