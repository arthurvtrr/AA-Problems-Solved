#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

int t, n, m;
long long p1, p2, nums[50050], dp[50050][110];

long long solve(int id, int left) {
    if (dp[id][left] != -1)
        return dp[id][left];
    if (id == n)
        return (left == m? 0 : left) * p2;

    long long ret = 10000000000000000;

    if (left >= nums[id])
        ret = solve(id+1, left - nums[id]);
    else if (left < nums[id]) {
        if (left > 0)
            ret = min(ret, solve(id+1, m) + (nums[id] - left) * p1);
        else
            ret = min(ret, solve(id, m));

        if (nums[id] <= m)
            ret = min(ret, solve(id, m) + left * p2);
    }

    return dp[id][left] = ret;
}

int main() {
    scanf("%d", &t);

    for (int tc = 0; tc < t; tc++) {
        scanf("%d %d", &n, &m);
        scanf("%lld %lld", &p1, &p2);

        for (int i = 0; i < n; i++)
            scanf("%lld", &nums[i]);

        for (int i = 0; i < 50050; i++)
            for (int j = 0; j < 110; j++)
                dp[i][j] = -1;

        printf("%lld\n", solve(0, m));
    }
    return 0;
}
