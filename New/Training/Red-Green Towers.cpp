#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define ll long long

int r, g;
ll dp[2][200200];

int main() {
    scanf("%d %d", &r, &g);

    int ini = 1, fim = 1000;
    while (ini <= fim) {
        int mid = (ini + fim) / 2;

        int x = r, y = g, atual = mid;

        while (atual) {
            if (x >= y && x >= atual) {
                x -= atual;
                atual--;
            }
            else if (y > x && y >= atual) {
                y -= atual;
                atual--;
            }
            else break;
        }

        if (atual > 0) fim = mid-1;
        else ini = mid+1;
    }

    ll h = fim;
    dp[1][0] = dp[1][1] = 1;

    for (int i = 2; i <= h; i++)
        for (int j = 0; j <= r; j++) {
            dp[i & 1][j] = dp[(i-1) & 1][j];
            if (j >= i) dp[i & 1][j] += dp[(i-1) & 1][j - i];

            dp[i & 1][j] %= MOD;
        }

    ll ans = 0;
    for (int i = 0; i <= r; i++)
        if (h * (h+1) / 2 - i <= g) {
            ans += dp[h & 1][i];
            ans %= MOD;
        }
    printf("%lld\n", ans);

    return 0;
}
