#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, root, parity[110000], times[110000], found = 0;
vector < int > places[110000], path;
bool visited[110000];

void dfs(int u, int pai) {
    visited[u] = true;
    path.push_back(u);
    times[u]++;
    for (int v : places[u]) {
        if (!visited[v]) {
            dfs(v, u);
            path.push_back(u);
            times[u]++;
        }
    }
    if (times[u] % 2 != parity[u] && u != pai) {
        path.push_back(pai);
        times[pai]++;
        path.push_back(u);
        times[u]++;
    }
}

int main()
{
    int a, b;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        visited[i] = true;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        visited[a] = false;
        visited[b] = false;
        places[a].push_back(b);
        places[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", &parity[i]);
    }

    if (m == 0) {
        for (int i = 1; i <= n; i++){
            if (parity[i] == 1) {
                path.push_back(i);
                found++;
            }
        }
    }
    else {
        for (int i = 1; i <= n; i++) {
            if(!visited[i]) {
                dfs(i, i);
                for(int u : path) {
                    if (parity[u] == 1) {
                        found++;
                        break;
                    }
                }
                if (found == 0) {
                    path.clear();
                }
            }
        }
    }

    if (found > 1) {
        printf("-1\n");
    }
    else if (found == 0) {
        printf("0\n");
    }
    else {
        int cont = 0;
        for (int u : path) {
            if (u == path.back())
                cont++;
        }
        if (cont % 2 != parity[path.back()]) {
            path.pop_back();
        }
        printf("%d\n", path.size());
        for (int i = 0; i < path.size(); i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    }

    return 0;
}