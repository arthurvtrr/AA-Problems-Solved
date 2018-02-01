#include <bits/stdc++.h>

using namespace std;

#define N 200100

int n, m, k, x, y;
set < pair <int, int> > edges;
vector < int > graph[N], trip;
bool visited[N];

void dfs(int u) {
    visited[u] = true;
    trip.push_back(u);

    for (int v : graph[u])
        if (!visited[v]) {
            dfs(v);
            trip.push_back(u);
        }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        if (x > y) swap(x, y);

        if (x != y && !edges.count(make_pair(x, y))) {
            graph[x].push_back(y);
            graph[y].push_back(x);
            edges.insert(make_pair(x, y));
        }
    }

    dfs(1);

    int pos = 0;
    for (int i = 0; i < k; i++) {
        int used = 0;
        int left = min((2*n + k-1) / k, (int)trip.size() - pos);
        if (left <= 0) {
            printf("1 1\n");
            continue;
        }

        printf("%d", left);
        while (used < (2*n + k-1) / k && pos < trip.size()) {
            printf(" ");
            printf("%d", trip[pos++]);
            used++;
        }
        printf("\n");
    }

    return 0;
}
