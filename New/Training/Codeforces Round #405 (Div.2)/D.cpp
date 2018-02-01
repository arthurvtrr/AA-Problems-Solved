#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, x, y;
ll jump;
vector < int > graph[200200];

struct state {
    ll len, cont, sum;
};

state dfs(int u, int p = -1) {
    state res = {0,1,0};

    for (int v : graph[u])
        if (v != p) {
          state aux = dfs(v, u);
          aux.len += 1 * aux.cont;

          res = {
            (res.len + aux.len + jump - 1) / jump,
            res.cont + aux.cont,
            res.sum + aux.len * res.cont + aux.sum + res.len * aux.cont
          };
        }

    return res;
}

int main() {
    scanf("%d %lld", &n, &jump);

    if (n == 1) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    printf("%lld\n", dfs(1).sum - (n + jump - 1) / jump);

    return 0;
}

