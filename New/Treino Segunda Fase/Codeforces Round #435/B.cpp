#include <bits/stdc++.h>

using namespace std;

int n, x, y, color[100100];
vector < int > graph[100100];

void dfs(int u, int p, int c) {
    color[u] = c;
    for (int v : graph[u])
        if (v != p)
            dfs(v, u, 1 - c);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1, 0, 0);

    long long a = 0, b = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) a++;
        else b++;
    }

    printf("%lld\n", a * b - n + 1);

    return 0;
}

