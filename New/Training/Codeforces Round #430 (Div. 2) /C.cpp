#include <bits/stdc++.h>

using namespace std;

int n, x, y, nums[200200], ans[200200];
vector < int > graph[200200];

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void dfs(int u, int p, int total, set < int > aux) {
    ans[u] = gcd(total, nums[u]);
    ans[u] = max(ans[u], total);
    for (int v : aux)
        ans[u] = max(ans[u], gcd(v, nums[u]));

    set < int > nxt;
    nxt.insert(total);
    for (int v : aux)
        nxt.insert(gcd(v, nums[u]));

    for (int v : graph[u])
        if (v != p)
            dfs(v, u, gcd(total, nums[u]), nxt);
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

    set < int > aux;
    dfs(1, 0, 0, aux);

    for (int i = 1; i <= n; i++) {
        if (i > 1) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}

