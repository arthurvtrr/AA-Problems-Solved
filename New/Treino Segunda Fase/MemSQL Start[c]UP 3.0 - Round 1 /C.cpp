#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, nums[55];
pii dp[55][2];

pii solve(int id, int p) {
    if (dp[id][p].first != -1) return dp[id][p];
    if (id == n) return pii(0, 0);

    pii ret = pii(0, 0);
    pii a = solve(id+1, 1 - p);
    ret = pii(a.second + nums[id], a.first);
    pii b = solve(id+1, p);
    pii aux = pii(b.first, b.second + nums[id]);
    if (aux.first > ret.first || (aux.first == ret.first && aux.second < ret.second))
        ret = aux;

    return dp[id][p] = ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < 55; i++)
        dp[i][0] = dp[i][1] = pii(-1, -1);

    pii ans = solve(0, 0);
    printf("%d %d\n", ans.second, ans.first);
    return 0;
}

