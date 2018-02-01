#include <bits/stdc++.h>

using namespace std;

int n, m, x, y;
set < int > graph[200200];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].insert(y);
        graph[y].insert(x);
    }

    bool possible = false;
    for (auto v : graph[1]) {
        if (graph[v].count(n))
            possible = true;
    }

    if (possible) printf("POSSIBLE\n");
    else printf("IMPOSSIBLE\n");

    return 0;
}
