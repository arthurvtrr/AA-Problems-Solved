#include <bits/stdc++.h>

using namespace std;

int n, q, nums[1 << 19];

#define N 1 << 19

struct Node {
    int val, acum, xacum, lvl, lft, rgt;

    void atualize(int x, int y) {
        if (x != 0) val = acum = x;
        if (y != 0) {
            if (y & (1 << lvl)) swap(lft, rgt);
            xacum ^= y;
        }
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum, xacum);
        right.atualize(acum, xacum);
        acum = xacum = 0;
    }

    void _merge(Node& left, Node& right) {
        val = max(left.val, right.val);
    }
} seg[4*N];

void build(int id, int ini, int fim, int l) {
    seg[id].lvl = l;
    seg[id].lft = 2*id;
    seg[id].rgt = 2*id+1;

    if (ini == fim) {
        seg[id].val = nums[ini];
        return;
    }

    int meio = (ini + fim) / 2;

    build(2*id, ini, meio, l-1);
    build(2*id+1, meio+1, fim, l-1);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

void update(int id, int ini, int fim, int start, int end, int val, int x) {
    if (start > fim || end < ini)
        return;
    if (ini >= start && fim <= end) {
        seg[id].atualize(val, x);
        return;
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[seg[id].lft], seg[seg[id].rgt]);

    update(seg[id].lft, ini, meio, start, end, val, x);
    update(seg[id].rgt, meio+1, fim, start, end, val, x);

    seg[id]._merge(seg[seg[id].lft], seg[seg[id].rgt]);
}

int query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id].val;

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[seg[id].lft], seg[seg[id].rgt]);

    return max(query(seg[id].lft, ini, meio, start, end), query(seg[id].rgt, meio+1, fim, start, end));
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= 1 << n; i++)
        scanf("%d", &nums[i]);

    build(1, 1, 1 << n, n-1);

    int t, x, y, z;
    for (int i = 0; i < q; i++) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &x, &y);
            printf("%d\n", query(1, 1, 1 << n, x+1, y+1));
        }
        else if (t == 2) {
            scanf("%d %d %d", &x, &y, &z);
            update(1, 1, 1 << n, x+1, y+1, z, 0);
        }
        else {
            scanf("%d", &x);
            update(1, 1, 1 << n, 1, 1 << n, 0, x);
        }
    }

    return 0;
}
