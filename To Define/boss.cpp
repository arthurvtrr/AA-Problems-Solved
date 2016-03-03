#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int idade[550];
int ind[550];
vector < int > graph[550];
vector < int > bosses[550];
int minimum;
bool visited[550];

void dfs(int u, int x) {
    visited[u] = true;
    for (int v : graph[u])
        if (!visited[v])
            dfs(v, x);
    bosses[x].push_back(u);
}

int main() {
    int n, m, I, x, y;
    char oper[5];
    while (scanf("%d %d %d", &n, &m, &I) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &idade[i]);
            ind[i] = i;
            graph[i].clear();
            bosses[i].clear();
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            graph[y].push_back(x);
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 550; j++)
                visited[j] = false;
            for (int u : graph[i])
                if (!visited[u])
                    dfs(u, i);
        }

        for (int i = 0; i < I; i++) {
            scanf("%s", oper);
            if (oper[0] == 'P') {
                minimum = 101;
                scanf("%d", &x);
                for (int boss : bosses[ind[x]])
                    if (idade[boss] < minimum)
                        minimum = idade[boss];
                if (minimum == 101) printf("*\n");
                else printf("%d\n", minimum);
            }
            else {
                scanf("%d %d", &x, &y);
                swap(idade[ind[x]], idade[ind[y]]);
                swap(ind[x], ind[y]);
            }
        }

    }
    return 0;
}
