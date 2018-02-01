#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define INF 1000000000000000000LL

int n;
ll b, c, h[6060], cost[6060][6060], dp[6060][6060], inv[6060];

void solve(int ini, int fim, int mini, int maxi, int lvl) {
    if (ini > fim) return;

    int mid = (ini + fim) / 2;

    int ind = mini;
    for (int i = mini; i < min(maxi+1, mid); i++)
        if (dp[mid][lvl] > dp[i][lvl-1] + cost[i][mid] + b) {
            ind = i;
            dp[mid][lvl] = dp[i][lvl-1] + cost[i][mid] + b;
        }

    solve(ini, mid-1, mini, ind, lvl);
    solve(mid+1, fim, ind, maxi, lvl);
}

int main() {
    scanf("%d %lld %lld", &n, &b, &c);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &h[i]);
        h[i] += h[i-1];
    }

    ll aux = 0;
    for (int i = 1; i <= n; i++) {
        cost[0][i] = aux;
        aux += h[i] * c;
    }

    aux = 0;
    for (int i = n; i >= 1; i--) {
        inv[i] = aux;
        aux += (h[n] - h[i-1]) * c;
    }

    for (int i = 1; i <= n; i++) {
        aux = 0;
        for (int j = i+2; j <= n; j++) {
            aux += (h[j-1] - h[j-1 - (j - i) / 2]) * c;
            cost[i][j] = aux;
        }
    }

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = INF;

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++)
        solve(0, n, 0, n, i);

    for (int i = 1; i <= n; i++) {
        if (i > 1) printf(" ");
        ll ans = dp[n][i];
        for (int j = 1; j < n; j++)
            ans = min(ans, dp[j][i] + inv[j]);
        printf("%lld", ans);
    }
    printf("\n");

    return 0;
}
