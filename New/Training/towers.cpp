#include <bits/stdc++.h>

using namespace std;

int n, nums[5050], acum[5050], dp[5050][5050], minv[5050][5050];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        acum[i] = nums[i];
        if (i) acum[i] += acum[i-1];
    }

    for (int i = 0; i < 5050; i++)
        for (int j = 0; j < 5050; j++) {
            dp[i][j] = 10000000;
            if (i) minv[i][j] = 10000000;
        }

    dp[0][1] = 0; minv[0][0] = 10000000;

    for (int i = 1; i < n; i++) {
        dp[i][i+1] = minv[i][i+1] = i;

        for (int j = 1; j <= i; j++) {
            int ini = 0, fim = i-j+1;
            while (ini <= fim) {
                int mid = (ini + fim) / 2;
                if (acum[i-j] - acum[i-j-mid] <= acum[i] - acum[i-j]) ini = mid+1;
                else fim = mid-1;
            }

            minv[i][j] = dp[i][j] = min(dp[i][j], minv[i-j][fim] + j - 1);
        }

        for (int j = 1; j < 5050; j++)
            minv[i][j] = min(minv[i][j], minv[i][j-1]);
    }

    int ans = 10000000;
    for (int i = 1; i <= n; i++)
        ans = min(ans, dp[n-1][i]);

    printf("%d\n", ans);

    return 0;
}
