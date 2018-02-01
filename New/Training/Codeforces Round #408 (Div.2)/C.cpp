#include <bits/stdc++.h>

using namespace std;

int n, a, b, strengh[300300];
vector < int > graph[300300];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &strengh[i]);

    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int ans = 2000000000;
    multiset < int > aux;
    for (int i = 1; i <= n; i++)
        aux.insert(strengh[i]);

    for (int i = 1; i <= n; i++) {
        int x = strengh[i];

        aux.erase(aux.find(strengh[i]));

        if (graph[i].size() > 0) {
            x = max(x, *(aux.rbegin()) + 1);

            for (int v : graph[i])
                aux.erase(aux.find(strengh[v]));

            if (!aux.empty()) x = max(x, *(aux.rbegin()) + 2);
        }

        aux.insert(strengh[i]);
        for (int v : graph[i])
            aux.insert(strengh[v]);

        ans = min(ans, x);
    }

    printf("%d\n", ans);

    return 0;
}
