#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, m, x, y, nums[100100];
vector < int > graph[100100];

bool visited[100100];
int aux;

void dfs(int u) {
    visited[u] = true;
    aux = min(aux, nums[u]);
    for (int v : graph[u])
        if (!visited[v])
            dfs(v);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++)
        if (!visited[i]) {
            aux = INT_MAX;
            dfs(i);
            ans += aux;
        }
    printf("%lld\n", ans);

    return 0;
}


