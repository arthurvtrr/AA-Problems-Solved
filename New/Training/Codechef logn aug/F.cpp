#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int t, n, m, x, y, ans[100100], lst[100100];
set < int > graph[100100], inv[100100], app[100100];
set < pii > edges;

int main() {
    scanf("%d", &t);
    while (t--) {
        edges.clear();
        for (int i = 0; i < 100100; i++) {
            graph[i].clear();
            inv[i].clear();
            app[i].clear();
        }

        scanf("%d %d", &n, &m);

        bool valid = true;
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            if (x < y) {
                if (edges.count(pii(x, y))) valid = false;
                graph[x].insert(y);
                inv[y].insert(x);
                edges.insert(pii(x, y));
            }
            else valid = false;
        }

        memset(lst, 0, sizeof lst);

        ans[0] = 1;
        for (int i = 1; i <= n; i++) {
            int aux = ans[*inv[i].begin()];

            for (int v : inv[i])
                while (app[v].count(aux)) aux++;

            ans[i] = aux;
            for (int v : inv[i])
                app[v].insert(aux);

            if (*inv[i].begin() != lst[aux] || inv[i].size() != i - lst[aux]) valid = false;
            lst[aux] = i;
        }

        if (!valid) printf("-1\n");
        else {
            for (int i = 1; i <= n; i++) {
                if (i > 1) printf(" ");
                printf("%d", ans[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
