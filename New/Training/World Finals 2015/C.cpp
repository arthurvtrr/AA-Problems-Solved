#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000

int n, k, dist[110][110], dp[110][110];

int main() {
    for (int i = 0; i < 110; i++)
        for (int j = 0; j < 110; j++) {
            dist[i][j] = (i == j? 0 : INF);
            dp[i][j] = INF;
        }

    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        for (int j = i+1; j <= n+1; j++) {
            scanf("%d", &dist[i][j]);
            dist[j][i] = dist[i][j];
        }

    for (int k = 0; k < 110; k++)
        for (int i = 0; i < 110; i++)
            for (int j = 0; j < 110; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    dp[1][k] = 0;

    for (int i = 2; i <= n+1; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = min(dp[i][j], dp[i-1][j+1] + dist[1][i]);
            for (int k = 2; k < i; k++)
                for (int l = j; l <= k; l++)
                    if (dp[k][l] < INF)
                        dp[i][j] = min(dp[i][j], dp[i-1][j] + dist[k][i]);
        }
    }

    int ans = INF;
    for (int i = 0; i <= k; i++)
        ans = min(ans, dp[n+1][i]);

    printf("%d\n", ans);

    return 0;
}

