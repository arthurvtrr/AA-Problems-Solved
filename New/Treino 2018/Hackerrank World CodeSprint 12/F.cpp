#include <bits/stdc++.h>

using namespace std;

int n, nums[200200], x, y;
vector < int > graph[200200];

unordered_map < int, int > dp[200200];

int solve(int u, int lst, int p) {
    if (dp[u].count(lst)) return dp[u][lst];

    int ret = 1;
    for (int v : graph[u])
        if (v != p)
            ret += solve(v, lst, u);

    if (nums[lst] <= nums[u]) {
        int aux = 0;
        for (int v : graph[u])
            if (v != p)
                aux += solve(v, u, u);
        ret = min(ret, aux);
    }

    return dp[u][lst] = ret;
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    nums[0] = 0;
    printf("%d\n", solve(1, 0, 0));

    return 0;
}
