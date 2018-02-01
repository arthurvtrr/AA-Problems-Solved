#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define INF 10000000000000000LL

int t, n, b, c, nums[3030];
ll dp[3030][3030];

void solve(int ini, int fim, int mini, int maxi, int lvl) {
    if (ini > fim) return;

    int mid = (ini + fim) / 2;

    int ind = mini;
    for (int i = mini; i < min(maxi+1, mid); i++) {
        ll x = nums[mid] - nums[i];
        if (dp[mid][lvl] > dp[i][lvl-1] + x*x) {
            ind = i;
            dp[mid][lvl] = dp[i][lvl-1] + x*x;
        }
    }

    solve(ini, mid-1, mini, ind, lvl);
    solve(mid+1, fim, ind, maxi, lvl);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &n, &b, &c);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= b; j++)
                dp[i][j] = INF;

        dp[0][0] = 0;
        for (int i = 1; i <= b; i++)
            solve(0, n-1, 0, n-1, i);

        printf("%lld\n", dp[n-1][b]);
    }
    return 0;
}
