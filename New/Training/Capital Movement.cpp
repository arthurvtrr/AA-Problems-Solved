#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int t, n, vals[50500], x, y;
vector < int > graph[50500];

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        for (int i = 0; i < 50500; i++)
            graph[i].clear();

        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &vals[i]);
        for (int i = 0; i < n-1; i++) {
            scanf("%d %d", &x, &y);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        set < pii > aux;

        for (int i = 1; i <= n; i++)
            aux.insert(pii(vals[i-1], i));

        for (int i = 1; i <= n; i++) {
            aux.erase(pii(vals[i-1], i));
            for (int v : graph[i])
                aux.erase(pii(vals[v-1], v));

            if (i > 1) printf(" ");
            printf("%d", (*aux.rbegin()).second);

            aux.insert(pii(vals[i-1], i));
            for (int v : graph[i])
                aux.insert(pii(vals[v-1], v));
        }
        printf("\n");
    }

    return 0;
}
