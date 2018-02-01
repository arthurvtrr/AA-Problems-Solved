#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007

int t, n, nums[55];
ll dp[110][110][110];

ll solve(int ind, int prv, int atual) {
    if (dp[ind][prv][atual] != -1) return dp[ind][prv][atual];

    int nw = atual + (ind >= n? 0 : nums[ind]);
    if ((prv == 0 || nw == 0) && ind >= n-1) return 1;

    ll ret = 0;
    for (int i = 0; i <= min(prv, nw); i++) {
        ret += solve(ind+1, nw - i, i);
        ret %= MOD;
    }

    return dp[ind][prv][atual] = ret;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        memset(dp, -1, sizeof dp);
        printf("%lld\n", solve(1, nums[0], 0));
    }
    return 0;
}
