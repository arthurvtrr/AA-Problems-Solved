#include <bits/stdc++.h>

using namespace std;

int a, b, h, w, n, nums[100100];
vector < int > to_use;

#define state vector < long long >
#define INF 1000000000

map < state, int > dp;

int solve(state s) {
    if (dp.count(s)) return dp[s];

    if ((s[1] >= a && s[2] >= b) || (s[1] >= b && s[2] >= a)) return 0;
    if (s[0] == to_use.size()) return INF;

    int ret = INF;
    ret = min(ret, 1 + solve(state({s[0]+1, s[1]*to_use[s[0]], s[2]})));
    ret = min(ret, 1 + solve(state({s[0]+1, s[1], s[2]*to_use[s[0]]})));
    return dp[s] = ret;
}

int main() {
    scanf("%d %d %d %d %d", &a, &b, &h, &w, &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    sort(nums, nums+n);

    for (int i = n-1; i >= max(0, n-1-33); i--)
        to_use.push_back(nums[i]);

    int ans = solve(state({0, h, w}));
    printf("%d\n", ans == INF? -1 : ans);

    return 0;
}

