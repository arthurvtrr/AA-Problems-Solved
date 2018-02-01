#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

int n, m, k, x, y, colors[200200];

vector < int > graph[200200];
map < int, int > found;
bool visited[200200];

void dfs(int u) {
    visited[u] = true;
    found[colors[u]]++;
    for (int v : graph[u])
        if (!visited[v])
            dfs(v);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &colors[i]);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int sol = 0;
    for (int i = 1; i <= n; i++) {
        found.clear();
        if (!visited[i]) dfs(i);
        int aux = 0, siz = 0;

        for (map < int, int >::iterator it = found.begin(); it != found.end(); it++) {
            if (it->second > aux)
                aux = it->second;
            siz += it->second;
        }

        sol += siz - aux;
    }

    printf("%d\n", sol);

    return 0;
}
