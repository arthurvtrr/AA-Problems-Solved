#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

int n, m, x, y;
vector < int > graph[100100];
int color[100100];
bool bipartite;

void dfs(int u, int c) {
    color[u] = c;
    for (int v : graph[u]) {
        if (color[v] == color[u]) bipartite = false;
        else if (color[v] == 0) dfs(v, 3 - c);
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    bipartite = true;

    for (int i = 1; i <= n; i++)
        if (color[i] == 0 && graph[i].size() != 0)
            dfs(i, 1);

    if (!bipartite) printf("-1\n");
    else {
        vector < int > A, B;

        for (int i = 1; i <= n; i++)
            if (color[i] == 1) A.push_back(i);
            else if (color[i] == 2) B.push_back(i);

        printf("%d\n", A.size());
        for (int i = 0; i < A.size(); i++) {
            if (i > 0) printf(" ");
            printf("%d", A[i]);
        }
        printf("\n");

        printf("%d\n", B.size());
        for (int i = 0; i < B.size(); i++) {
            if (i > 0) printf(" ");
            printf("%d", B[i]);
        }
        printf("\n");
    }
    return 0;
}
