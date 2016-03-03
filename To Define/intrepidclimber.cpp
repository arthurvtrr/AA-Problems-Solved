#include <stdio.h>
#include <vector>

using namespace std;

typedef pair < int, int > pii;

int friends[110000], totald, maxd;
vector < pii > graph[110000];
bool visited[110000];

void dfs(int u, int d1, int lastf) {
    if (friends[u]) {
        lastf = d1;
        if (maxd < d1) maxd = d1;
    }
    visited[u] = true;

    if (graph[u].size() == 0)
        totald += lastf;

    for (pii v : graph[u])
        if (!visited[v.first])
            dfs(v.first, d1 + v.second, lastf);
}

int main() {
    int n, f, x, y, z;
    while (scanf("%d %d", &n, &f) != EOF) {
        totald = maxd = 0;
        for (int i = 0; i < 110000; i++) {
            graph[i].clear();
            friends[i] = 0;
            visited[i] = false;
        }
        for (int i = 0; i < n-1; i++) {
            scanf("%d %d %d", &x, &y, &z);
            graph[x].push_back(make_pair(y,z));
        }
        for (int i = 0; i < f; i++) {
            scanf("%d", &x);
            friends[x]++;
        }

        dfs(1,0,0);
        printf("%d\n", totald - maxd);
    }
    return 0;
}
