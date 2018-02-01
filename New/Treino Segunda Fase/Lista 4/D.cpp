#include <bits/stdc++.h>

using namespace std;

int n, x, cnt[2][15], pow3[15], dp[1600000];

int solve(int mask) {
    if (dp[mask] != -1) return dp[mask];

    int ret = 0, quant[15], aux = mask;
    memset(quant, 0, sizeof quant);

    for (int i = 0; i < 13; i++) {
        quant[i+1] = aux % 3;
        aux /= 3;
    }

    for (int i = 1; i < 14; i++)
        for (int j = 1; j <= i; j++)
            for (int k = 1; k <= i; k++) {
                quant[i]--; quant[j]--; quant[k]--;
                if (quant[i] >= 0 && quant[j] >= 0 && quant[k] >= 0 && j+k > i)
                    ret = max(ret, 1 + solve(mask - pow3[i-1] - pow3[j-1] - pow3[k-1]));
                quant[i]++; quant[j]++; quant[k]++;
            }

    return dp[mask] = ret;
}

int main() {
    pow3[0] = 1;
    for (int i = 1; i < 15; i++)
        pow3[i] = pow3[i-1] * 3;
    memset(dp, -1, sizeof dp);

    while (scanf("%d", &n), n) {
        memset(cnt, 0, sizeof cnt);

        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            cnt[i % 2][x]++;
        }

        int p[2] = {0, 0}, c[2] = {0, 0};
        for (int i = 0; i < 2; i++)
            for (int j = 1; j < 14; j++) {
                p[i] += cnt[i][j] / 3;
                cnt[i][j] %= 3;
            }

        if (p[0] < p[1]) printf("2\n");
        else if (p[0] > p[1]) printf("1\n");
        else {
            int ini = 0;
            for (int i = 0; i < 13; i++)
                ini += cnt[0][i+1] * pow3[i];
            c[0] = solve(ini);
            ini = 0;
            for (int i = 0; i < 13; i++)
                ini += cnt[1][i+1] * pow3[i];
            c[1] = solve(ini);

            if (c[0] < c[1]) printf("2\n");
            else if (c[0] > c[1]) printf("1\n");
            else printf("0\n");
        }
    }
    return 0;
}
