#include <bits/stdc++.h>

using namespace std;

vector < int > graph[100100];
int n, x, y;
double ans;

void dfs(int u, int p, int d, double pb) {
    double div = graph[u].size()-1 + (u == 1);

    for (int v : graph[u])
        if (v != p)
            dfs(v, u, d+1, pb / div);

    if (graph[u].size() == 1)
        ans += d * pb;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    ans = 0.0;
    dfs(1, 0, 0, 1.0);
    printf("%.10f\n", ans);

    return 0;
}

