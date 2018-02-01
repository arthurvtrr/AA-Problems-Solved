#include <bits/stdc++.h>

using namespace std;

#define N 50500
#define ll long long

struct Node {
    ll val, acum, siz;

    void atualize(ll x) {
        val += x * siz;
        acum += x;
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum);
        right.atualize(acum);
        acum = 0;
    }

    void _merge(Node& left, Node& right) {
        val = left.val + right.val;
    }

} seg[2][4*N];

ll nums[2][N];

void build(int id, int ini, int fim, int p) {
    seg[p][id].siz = fim - ini + 1;

    if (ini == fim) {
        seg[p][id].val = nums[p][ini];
        return;
    }

    int meio = (ini + fim) / 2;

    build(2*id, ini, meio, p);
    build(2*id+1, meio+1, fim, p);

    seg[p][id]._merge(seg[p][2*id], seg[p][2*id+1]);
}

void update(int id, int ini, int fim, int start, int end, int val, int p) {
    if (start > fim || end < ini)
        return;
    if (ini >= start && fim <= end) {
        seg[p][id].atualize(val);
        return;
    }

    int meio = (ini + fim) / 2;
    seg[p][id].shift(seg[p][2*id], seg[p][2*id+1]);

    update(2*id, ini, meio, start, end, val, p);
    update(2*id+1, meio+1, fim, start, end, val, p);

    seg[p][id]._merge(seg[p][2*id], seg[p][2*id+1]);
}

ll query(int id, int ini, int fim, int start, int end, int p) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[p][id].val;

    int meio = (ini + fim) / 2;
    seg[p][id].shift(seg[p][2*id], seg[p][2*id+1]);

    return query(2*id, ini, meio, start, end, p) + query(2*id+1, meio+1, fim, start, end, p);
}

int n, m, q, a[100100], b[100100];
int l, r, x;
ll sum[2][100100];
vector < ll > vals;

ll solve(ll x) {
    int ini = 0, fim = vals.size()-1;
    while (ini <= fim) {
        int mid = (ini + fim) / 2;
        if (vals[mid] < -x) ini = mid+1;
        else fim = mid-1;
    }

    ll ret = LLONG_MAX;
    for (int i = max(0, ini-3); i < min((int)vals.size(), ini+3); i++)
        ret = min(ret, abs(vals[i] + x));
    return ret;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]);

    int pos = 1;
    for (int i = 1; i <= n; i += 2)
        nums[0][pos++] = a[i];
    pos = 1;
    for (int i = 2; i <= n; i += 2)
        nums[1][pos++] = a[i];

    for (int i = 1; i <= m; i++) {
        sum[i % 2][i] = b[i];
        sum[0][i] += sum[0][i-1];
        sum[1][i] += sum[1][i-1];
    }

    build(1, 1, N-1, 0);
    build(1, 1, N-1, 1);

    for (int i = 0; i <= m - n; i++) {
        ll val = 0;
        int l = 1 + i, r = n + i;
        val += sum[i % 2][r] - sum[i % 2][l-1];
        val -= sum[i % 2 == 0][r] - sum[i % 2 == 0][l-1];
        vals.push_back(val);
    }

    sort(vals.begin(), vals.end());

    ll q1 = query(1, 1, N-1, 1, N-1, 0), q2 = query(1, 1, N-1, 1, N-1, 1);
    printf("%lld\n", solve(q1 - q2));

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &l, &r, &x);

        if (l == r) {
            if (l % 2 == 1) update(1, 1, N-1, (l + 1) / 2, (r + 1) / 2, x, 0);
            else update(1, 1, N-1, l / 2, r / 2, x, 1);
        }
        else {
            update(1, 1, N-1, (l + (l % 2 == 0) + 1) / 2, (r + 1) / 2, x, 0);
            update(1, 1, N-1, (l + (l % 2)) / 2, r / 2, x, 1);
        }

        q1 = query(1, 1, N-1, 1, N-1, 0), q2 = query(1, 1, N-1, 1, N-1, 1);
        printf("%lld\n", solve(q1 - q2));
    }

    return 0;
}

