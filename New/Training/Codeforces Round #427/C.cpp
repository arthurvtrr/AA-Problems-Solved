#include <bits/stdc++.h>

using namespace std;

int n, q, l, t, a, b, c, d;
int cnt[12][110][110];

struct star {
    int x, y, s;
} stars[100100];

int main() {
    scanf("%d %d %d", &n, &q, &l);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &stars[i].x, &stars[i].y, &stars[i].s);
        cnt[stars[i].s][stars[i].x][stars[i].y]++;
    }

    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 110; j++)
            for (int k = 0; k < 110; k++) {
                if (j > 0) cnt[i][j][k] += cnt[i][j-1][k];
                if (k > 0) cnt[i][j][k] += cnt[i][j][k-1];
                if (j > 0 && k > 0) cnt[i][j][k] -= cnt[i][j-1][k-1];
            }

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d %d %d", &t, &a, &b, &c, &d);

        int ans = 0;
        for (int j = 0; j < 12; j++) {
            int quant = cnt[j][c][d] - cnt[j][a-1][d] - cnt[j][c][b-1] + cnt[j][a-1][b-1];
            ans += quant * ((j + t) % (l+1));
        }
        printf("%d\n", ans);
    }

    return 0;
}

