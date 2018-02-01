#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

#define INF 1000000000000LL

int t, n, m, k, x, y, z, ini[5500], fim[5500];
long long dist[110][110], dp[5500][110][5];

void floydWarshall() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            if (i != k && dist[i][k] < INF)
                for (int j = 1; j <= n; j++)
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
}

long long solve(int id, int city, int used) {
    if (dp[id][city][used] != -1)
        return dp[id][city][used];

    if (id == k) return 0;

    long long ret = INF;

    if (used == 0)
        ret = min(ret, dist[city][ini[id]] + solve(id, ini[id], 1));
    else {
        ret = min(ret, dist[city][fim[id]] + solve(id+1, fim[id], 0));
        if (id < k-1) ret = min(ret, dist[city][ini[id+1]] + dist[ini[id+1]][fim[id]] + solve(id+1, fim[id], 1));
    }

    return dp[id][city][used] = ret;
}

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {

        for (int i = 0; i < 110; i++)
            for (int j = 0; j < 110; j++)
                dist[i][j] = (i == j? 0LL : INF);

        scanf("%d %d %d", &n, &m, &k);
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &z);
            dist[x][y] = dist[y][x] = min(dist[x][y], (long long) z);
        }

        for (int i = 0; i < k; i++)
            scanf("%d %d", &ini[i], &fim[i]);

        floydWarshall();

        for (int i = 0; i < 5500; i++)
            for (int j = 0; j < 110; j++)
                for (int k = 0; k < 5; k++)
                    dp[i][j][k] = -1;

        long long sol = solve(0, 1, 0);
        printf("Case #%d: %lld\n", tc+1, sol >= INF? -1LL : sol);
    }

    return 0;
}
