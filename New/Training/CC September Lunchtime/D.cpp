#include <bits/stdc++.h>

using namespace std;

int t, n, x, y, ans;
long long nums[100100];
vector < int > graph[100100];

bool cube(long long x) {
    long long ini = 1, fim = 1000000;
    while (ini <= fim) {
        long long mid = (ini + fim) / 2;
        if (mid * mid * mid == x) return true;
        else if (mid * mid * mid < x) ini = mid+1;
        else fim = mid-1;
    }
    return false;
}

void dfs(int u, int p, long long val, int siz) {
    if (cube(val)) ans = max(ans, siz);

    for (int v : graph[u])
        if (v != p)
            dfs(v, u, val * nums[v], siz+1);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < 20; i++)
            graph[i].clear();

        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &nums[i]);

        for (int i = 0; i < n-1; i++) {
            scanf("%d %d", &x, &y);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        ans = -1;
        for (int i = 1; i <= n; i++)
            dfs(i, 0, nums[i], 1);

        printf("%d\n", ans);
    }
    return 0;
}
