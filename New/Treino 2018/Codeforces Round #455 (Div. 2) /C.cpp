#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007

int n;
char tps[5050];
ll dp[5050][5050];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf(" %c", &tps[i]);

    dp[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        if (tps[i-1] == 'f') {
            for (int j = n; j > 0; j--)
                dp[i][j] = dp[i-1][j-1];
        }
        else {
            ll aux = 0;
            for (int j = n; j > 0; j--) {
                aux += dp[i-1][j];
                aux %= MOD;
                dp[i][j] = aux;
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dp[n][i];
        ans %= MOD;
    }
    printf("%lld\n", ans);

    return 0;
}
