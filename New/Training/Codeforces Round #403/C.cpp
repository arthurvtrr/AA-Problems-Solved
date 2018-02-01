#include <bits/stdc++.h>

using namespace std;

#define N 200100

int n, x, y, color[N];
vector < int > graph[N], colors;

void set_colors(int u, int p) {
    if (u == 1) color[u] = 1;

    int pos = 0;
    for (int v : graph[u])
        if (v != p) {
            while (colors[pos] == color[u] || colors[pos] == color[p])
                pos++;
            color[v] = colors[pos];
            pos++;
            set_colors(v, u);
        }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int k = 0;
    for (int i = 1; i <= n; i++)
        k = max(k, (int)graph[i].size() + 1);

    for (int i = 1; i <= k; i++)
        colors.push_back(i);

    set_colors(1, 0);

    printf("%d\n", k);
    for (int i = 1; i <= n; i++) {
        if (i > 1) printf(" ");
        printf("%d", color[i]);
    }
    printf("\n");

    return 0;
}
