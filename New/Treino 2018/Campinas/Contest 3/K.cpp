#include <bits/stdc++.h>

using namespace std;

int n, m, nums[303], lst[303], dp[300][300][301];

int solve(int ini, int fim, int val) {
    if (ini > fim) return 0;
    if (dp[ini][fim][val] != -1) return dp[ini][fim][val];
    if (nums[ini] == val) return dp[ini][fim][val] = solve(ini+1, fim, val);
    if (nums[fim] == val) return dp[ini][fim][val] = solve(ini, fim-1, val);

    int ret = 100000000;
    for (int i = ini; i <= min(fim, lst[nums[ini]]); i++)
        ret = min(ret, 1 + solve(ini, i, nums[ini]) + solve(i+1, fim, val));

    return dp[ini][fim][val] = ret;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        lst[nums[i]] = i;
    }

    memset(dp, -1, sizeof dp);

    int ans = INT_MAX;
    for (int i = 1; i <= m; i++)
        ans = min(ans, solve(0, n-1, i));

    printf("%d\n", ans);

    return 0;
}
