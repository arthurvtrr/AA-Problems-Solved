#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

#define INF 10000000000000000LL

int n, x, y;
long long pleas[200200], siz[200200], maxst[200200], dp[200200];
vector < int > graph[200200];

void calcsiz(int u, int p) {
    if (siz[u] != -INF)
        return;

    siz[u] = pleas[u];

    for (int v : graph[u])
        if (v != p) {
            calcsiz(v, u);
            siz[u] += siz[v];
        }
}

void calcst(int u, int p) {
    if (maxst[u] != -INF)
        return;

    maxst[u] = siz[u];

    for (int v : graph[u])
        if (v != p) {
            calcst(v, u);
            maxst[u] = max(maxst[u], maxst[v]);
        }
}

long long solve(int id, int p) {
    if (dp[id] != -INF)
        return dp[id];

    if (graph[id].size() < (id == 1? 2 : 3)) {
        for (int v : graph[id])
            if (v != p)
                return dp[id] = solve(v, id);
        return -INF - 1;
    }

    long long aux = 0, cont = 0;

    for (int v : graph[id])
        if (v != p) {
            cont++;
            aux += maxst[v];
            if (cont == 2) break;
        }

    dp[id] = max(dp[id], aux);

    cont = 0;
    for (int v : graph[id]) {
        if (v != p) {
            cont++;
            dp[id] = max(dp[id], solve(v, id));
            if (cont == 2) break;
        }
    }

    return dp[id];
}

bool cmp(int a, int b) {
    return maxst[a] > maxst[b];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &pleas[i]);

    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int cont[2] = {0, 0};

    for (int i = 2; i <= n; i++)
        if (graph[i].size() < 3)
            cont[graph[i].size()-1]++;

    if (cont[0] == min(n-1, 1) && cont[1] == max(0, n-2)) printf("Impossible\n");
    else {
        for (int i = 0; i < 200200; i++)
            maxst[i] = siz[i] = dp[i] = -INF;

        calcsiz(1, -1);
        calcst(1, -1);

        for (int i = 1; i <= n; i++)
            sort(graph[i].begin(), graph[i].end(), cmp);

        printf("%lld\n", solve(1, -1));
    }

    return 0;
}

/*
11
-1 2 4 -1 3 3 7 -2 -7 20 9
1 2
2 3
3 4
4 5
2 6
1 7
7 8
8 9
8 10
7 11
*/
