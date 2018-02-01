#include <bits/stdc++.h>

using namespace std;

#define MOD 10000000007
#define ll long long

int n, nums[55];
ll dp[55][55];

ll solve(int pos, int nxt) {
    if (dp[pos][nxt] != -1) return dp[pos][nxt];
    if (nxt >= n) {
        for (int i = 0; i < (1 << (nxt - pos)); i++)

    }
    ll ret = 0;

    return dp[pos][nxt] = ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    printf("%lld\n", solve(1, nums[0] + 1));

    return 0;
}
