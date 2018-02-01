#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

#define INF 1000000000000000000LL

int n, k, weight[1010], pos[1010];
long long dp[1010][1010], cost[1010][1010];

void solve(int ini, int fim, int mini, int maxi, int lvl) {
    if (ini > fim) return;

    int mid = (ini + fim) / 2;

    int ind = mini;
    for (int i = mini; i < min(maxi+1, mid); i++)
        if (dp[mid][lvl] > dp[i][lvl-1] + cost[i+1][mid]) {
            ind = i;
            dp[mid][lvl] = dp[i][lvl-1] + cost[i+1][mid];
        }

    solve(ini, mid-1, mini, ind, lvl);
    solve(mid+1, fim, ind, maxi, lvl);
}

int main() {
    while (scanf("%d %d", &n, &k) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d %d", &pos[i], &weight[i]);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < k; j++)
                dp[i][j] = i < j? 0 : INF;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cost[i][j] = 0;

        long long total, aux;
        for (int i = 0; i < n; i++) {
            total = 0, aux = 0;
            for (int j = i; j < n; j++) {
                cost[i][j] = total;
                aux += weight[j];
                total += aux * (pos[j+1] - pos[j]);
            }
        }

        for (int i = 0; i < n; i++)
            dp[i][0] = cost[0][i];

        for (int i = 1; i < k; i++)
            solve(0, n-1, 0, n-1, i);

        printf("%lld\n", dp[n-1][k-1]);
    }
    return 0;
}
