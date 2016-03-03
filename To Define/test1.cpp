#include <stdio.h>
#include <algorithm>
#include <iostream>

#define INF 2000000000

using namespace std;

int nums[2200], dp[2200][22];

int val(int x) {
    if (x % 10 < 5) return x - (x % 10);
    return x - (x % 10) + 10;
}

int main() {
    int n, d;
    while(scanf("%d %d", &n, &d) != EOF) {
        for (int i = 1; i <= n; i++)
            scanf("%d", &nums[i]);

        for (int i = 0; i < 2200; i++)
            for (int j = 0; j < 22; j++)
                dp[i][j] = 0;

        for (int i = 1; i < n; i++)
            for (int j = 0; j <= d; j++) {
                if (j == 0) dp[i][j] += dp[i-1][j]+nums[i];
                else dp[i][j] = min(dp[i-1][j]+nums[i], val(dp[i-1][j-1]+nums[i]));
            }

        int sol = INF;
        for (int i = 0; i <= d; i++)
            sol = min(val(dp[n-1][i]+nums[n]),sol);
        cout << sol << "\n";
    }
    return 0;
}

