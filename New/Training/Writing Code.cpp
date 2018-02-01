#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, m, b, bugs[550];
ll mod, dp[505][505];

int main() {
    scanf("%d %d %d %lld", &n, &m, &b, &mod);
    for (int i = 0; i < n; i++)
        scanf("%d", &bugs[i]);

    for (int i = 0; i <= b; i++)
        dp[0][i] = 1;

    for (int i = 0; i < n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 0; k <= b; k++)
                if (k >= bugs[i]) {
                    dp[j][k] += dp[j-1][k - bugs[i]];
                    dp[j][k] %= mod;
                }

    printf("%lld\n", dp[m][b]);

    return 0;
}
