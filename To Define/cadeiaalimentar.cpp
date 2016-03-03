#include <stdio.h>
#include <vector>
using namespace std;

vector < int > graph[110000];
bool visited[110000];
bool rec[110000];
bool cycle = false;

void dfs(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) {
            rec[u] = true;
            dfs(v);
            rec[u] = false;
        }
        else if (rec[v]) cycle = true;
    }
}

int main() {
    int n, m, x, y;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i])
            dfs(i);
    }
    if (cycle) printf("Bolada\n");
    else printf("Nao Bolada\n");
    return 0;
}
