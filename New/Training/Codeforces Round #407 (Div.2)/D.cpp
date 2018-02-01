#include <bits/stdc++.h>

using namespace std;

int n, m, x, y, ini;
vector < int > graph[1000100];
bool visited[1000100], used[1000100];

void dfs(int u) {
    visited[u] = true;
    for (int v : graph[u])
        if (!visited[v])
            dfs(v);
}

int main() {
    scanf("%d %d", &n, &m);
    long long loops = 0;

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        used[x] = used[y] = true;
        ini = x;

        if (x != y) graph[y].push_back(x);
        else loops++;
    }

    dfs(ini);

    int cont = 0, use = 0;
    for (int i = 1; i <= n; i++) {
        cont += visited[i];
        use += used[i];
    }

    if (cont != use) printf("0\n");
    else {
        long long ans = loops * (loops - 1) / 2;
        ans += loops * (m - loops);

        for (int i = 1; i <= n; i++) {
            long long cnt = 0;

            for (int v : graph[i])
                if (v != i)
                    cnt++;

            ans += cnt * (cnt-1) / 2;
        }

        printf("%lld\n", ans);
    }

    return 0;
}
