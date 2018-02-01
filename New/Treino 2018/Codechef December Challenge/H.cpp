#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007

int t, n, q, x, y, typ, a, b, c, d;

vector < int > graph[300300];
ll val[300300], fib[300300];

ll f(int x) {
    if (x == 0) return c;
    if (x == 1) return d;

    ll ret = fib[x-2]*c;
    ret %= MOD;
    ret += fib[x-1]*d;
    return ret % MOD;
}

void dfs(int u, int p, int dist) {
    if (dist == -1) return;

    val[u] += f(b - dist);
    val[u] %= MOD;
    for (int v : graph[u])
        if (v != p)
            dfs(v, u, dist-1);
}

int main() {
    fib[0] = fib[1] = 1;
    for (int i = 2; i < 300300; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        fib[i] %= MOD;
    }

    scanf("%d", &t);
    while (t--) {
        for (int i = 1; i <= n; i++) {
            val[i] = 0;
            graph[i].clear();
        }

        scanf("%d %d", &n, &q);
        for (int i = 0; i < n-1; i++) {
            scanf("%d %d", &x, &y);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        for (int i = 0; i < q; i++) {
            scanf("%d", &typ);
            if (typ == 1) {
                scanf("%d %d %d %d", &a, &b, &c, &d);
                dfs(a, 0, b);
            }
            else {
                scanf("%d", &a);
                printf("%lld\n", val[a]);
            }
        }
    }

    return 0;
}
