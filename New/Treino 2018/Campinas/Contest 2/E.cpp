#include <bits/stdc++.h>

using namespace std;

#define N 300300

int n, k, nums[N][3];
map < int, vector < int > > aux;

int sum[N];

struct Node {
    int val;
    int acum;

    void atualize(int x) {
        val = x + val;
        acum += x;
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum);
        right.atualize(acum);
        acum = 0;
    }

    void _merge(Node& left, Node& right) {
        val = max(left.val, right.val);
    }

} seg[4*N];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id].val = sum[ini];
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

    return max(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

int main() {
    scanf("%d %d", &n, &k);

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &nums[i][j]);
            aux[k - nums[i][j]].push_back(i);
            sum[i] += nums[i][j];
        }
        ans = max(ans, sum[i]);
    }

    build(1, 1, n);

    int lst = 0;
    for (auto p : aux) {
        update(1, 1, n, 1, n, 3*(p.first - lst));
        for (int v : p.second)
            update(1, 1, n, v, v, -k);

        ans = min(ans, query(1, 1, n, 1, n));
        lst = p.first;
    }
    printf("%d\n", ans);

    return 0;
}
