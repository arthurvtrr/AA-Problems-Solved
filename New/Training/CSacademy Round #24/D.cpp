#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

int n, h;
long long dp[510][510];

int main() {
    scanf("%d %d", &n, &h);
    dp[1][0] = 1; dp[1][1] = 1; dp[2][0] = 1;

    for (int i = 2; i <= 500; i++) {
        dp[1][i] = 0;
        dp[i+1][0] = 1;
    }

    for (int i = 2; i <= 501; i++)
        for (int j = 1; j <= 500; j++) {
            long long sum = 0;
            for (int k = 1; k <= j; k++) {
                sum += (dp[i - 1][k - 1] * dp[i - 1][j - k]) % MOD;
                sum %= MOD;
            }
            dp[i][j] = sum;
        }

    printf("%lld\n", (((dp[h][n] - dp[h-1][n]) % MOD) + MOD) % MOD);

    return 0;
}

