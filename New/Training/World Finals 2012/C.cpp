#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000

int n, m, x, y, z, dist[22][22];

void floydWarshall() {
    for (int k = 0; k < 22; k++)
        for (int i = 0; i < 22; i++)
            for (int j = 0; j < 22; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

vector < int > use[2];
int dp[262500][21][21];

int solve(int mask, int prev, int fim) {
    if (dp[mask][prev][fim] != -1) return dp[mask][prev][fim];
    if (__builtin_popcount(mask) == 1) return dist[prev][fim];

    int ret = INF;
    for (int i = 0; i < n-2; i++)
        if (mask & (1 << i) && i+1 != fim)
            ret = min(ret, dist[prev][i+1] + solve(mask ^ (1 << i), i+1, fim));

    return dp[mask][prev][fim] = ret;
}

int main() {
    int t = 1;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < 22; i++)
            for (int j = 0; j < 22; j++)
                dist[i][j] = (i != j? INF : 0);

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &z);
            dist[x][y] = dist[y][x] = z;
        }

        floydWarshall();
        memset(dp, -1, sizeof dp);

        if (n == 3) {
            printf("Case %d: %d\n", t++, 2*dist[0][1] + 2*dist[1][2]);
            continue;
        }

        int ans = INF;
        for (int i = 0; i < 1 << (n-2); i++) {
            if (__builtin_popcount(i) != (n-2) / 2) continue;

            int inv = 0;
            use[0].clear(); use[1].clear();

            for (int j = 0; j < n-2; j++) {
                if (i & (1 << j)) use[0].push_back(j+1);
                else {
                    use[1].push_back(j+1);
                    inv += 1 << j;
                }
            }

            for (int a = 0; a < use[0].size(); a++)
                for (int c = 0; c < use[0].size(); c++)
                    for (int b = 0; b < use[1].size(); b++)
                        for (int d = 0; d < use[1].size(); d++) {
                            int aux = dist[use[0][a]][use[1][b]] + dist[use[0][c]][use[1][d]];
                            aux += solve(i, 0, use[0][a]) + solve(i, n-1, use[0][c]);
                            aux += solve(inv, n-1, use[1][b]) + solve(inv, 0, use[1][d]);
                            ans = min(ans, aux);
                        }
        }
        printf("Case %d: %d\n", t++, ans);
    }

    return 0;
}
