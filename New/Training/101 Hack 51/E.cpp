#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define ll long long

int n, m, q, cnt[22][1010][2020], pos[5050];
char grid[1010][2020];
ll ans[22];

struct qr {
    int t, ind;
} qrs[22];

bool cmp(qr a, qr b) {
    return a.t < b.t;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", grid[i]);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &qrs[i].t);
        qrs[i].ind = i;
    }
    sort(qrs, qrs+q, cmp);

    for (int i = 0; i < 5050; i++) {
        pos[i] = q;
        for (int j = 0; j < q; j++)
            if (qrs[j].t >= i) {
                pos[i] = j;
                break;
            }
    }

    for (int i = 1; i < n-1; i++)
        for (int j = 0; j < 2*m - 1; j += 2)
            for (int a = 1; a < n-1; a++)
                for (int b = 0; b < 2*m - 1; b += 2)
                    if (grid[a][b] == 't') {
                        int dist;
                        if (b == j) dist = abs(i - a);
                        else dist = min(i + a + abs(b - j), 2*n-2 - i - a + abs(b - j));
                        cnt[pos[dist]][i][j]++;
                    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2*m; j++)
            for (int a = 0; a < q; a++) {
                if (a) cnt[a][i][j] += cnt[a-1][i][j];
                ll add = cnt[a][i][j];
                add *= add;
                add %= MOD;
                add *= i+1;
                add *= j+1;
                ans[qrs[a].ind] += add;
                ans[qrs[a].ind] %= MOD;
            }

    for (int i = 0; i < q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}

