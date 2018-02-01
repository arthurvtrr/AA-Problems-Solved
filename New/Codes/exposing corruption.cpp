#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define JUMP 105

int D, P, R, B, price[220], dp[220][10100];

vector < int > graph[220];

int comp_d, comp_p, cost[220], gain_d[220], gain_p[220];
bool visited[220];

int solve(int id, int remain) {
    if (dp[id][remain] != 300)
        return dp[id][remain];

    if (id == comp_d)
        return P;
    if (id == comp_p)
        return D;

    return dp[id][remain] = max(cost[id] > remain? 0 : ((id >= JUMP? gain_d[id] : gain_p[id]) + solve(id+1, remain-cost[id])), solve(id+1, remain));
}

void dfs(int u, int comp) {
    visited[u] = true;
    cost[comp] += price[u];
    gain_d[comp] += (comp >= JUMP && u < JUMP? -1 : 0);
    gain_d[comp] += (comp >= JUMP && u >= JUMP? 1 : 0);
    gain_p[comp] += (comp < JUMP && u >= JUMP? -1 : 0);
    gain_p[comp] += (comp < JUMP && u < JUMP? 1 : 0);

    for (int v : graph[u])
        if (!visited[v])
            dfs(v, comp);
}

int main() {
    while (scanf("%d %d %d %d", &D, &P, &R, &B) != EOF) {
        for (int i = 0; i < 220; i++) {
            graph[i].clear();
            cost[i] = gain_d[i] = gain_p[i] = visited[i] = price[i] = 0;

            for (int j = 0; j < 10100; j++)
                dp[i][j] = 300;
        }

        for (int i = 0; i < D; i++)
            scanf("%d", &price[i]);
        for (int i = 0; i < P; i++)
            scanf("%d", &price[i+JUMP]);

        int a, b;
        for (int i = 0; i < R; i++) {
            scanf("%d %d", &a, &b);
            graph[a-1].push_back(b-1+JUMP);
            graph[b-1+JUMP].push_back(a-1);
        }

        comp_d = 0;
        for (int i = 0; i < D; i++)
            if (!visited[i]) {
                dfs(i, comp_d);
                comp_d++;
            }

        for (int i = 0; i < 220; i++)
            visited[i] = false;

        comp_p = JUMP;
        for (int i = JUMP; i < JUMP+P; i++)
            if (!visited[i]) {
                dfs(i, comp_p);
                comp_p++;
            }

        printf("%d %d\n", solve(JUMP, B), solve(0, B));
    }
    return 0;
}
