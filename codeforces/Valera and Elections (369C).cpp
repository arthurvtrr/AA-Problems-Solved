#include <stdio.h>
#include <vector>

using namespace std;

int n, k, neigh[110000], danif[110000];
vector < int > districts[110000];
vector < int > candidates;

void dfs(int u, int pai) {
    neigh[u] = danif[u];
    for (int v : districts[u]) {
        if (v != pai) {
            dfs(v, u);
            neigh[u] += neigh[v];
        }
    }
}

int main()
{
    int a, b, t;
    scanf("%d", &n);
    for(int i = 0; i < n-1; i++) {
        scanf("%d %d %d", &a, &b, &t);
        districts[a].push_back(b);
        districts[b].push_back(a);
        if (t == 2) {
            danif[a] = 1;
            danif[b] = 1;
        }
    }

    dfs(1, -1);
    for (int i = 1; i <= n; i++) {
        if(neigh[i] == 1 && danif[i] == 1)
            candidates.push_back(i);
    }
    printf("%d\n", candidates.size());
    for(int i : candidates)
        printf("%d ", i);
    printf("\n");

    return 0;
}