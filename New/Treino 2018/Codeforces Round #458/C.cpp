#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007

string n;
int k;
ll dp[1010][1010][2];

ll solve(int ind, int lft, int f) {
    if (dp[ind][lft][f] != -1) return dp[ind][lft][f];
    if (ind == n.size()) return (lft == 0);

    ll ret = 0;
    if (f || n[ind] == '1') {
        if (lft) {
            ret += solve(ind+1, lft-1, f);
            ret %= MOD;
        }
        ret += solve(ind+1, lft, 1);
        ret %= MOD;
    }
    else {
        ret += solve(ind+1, lft, f);
        ret %= MOD;
    }

    return dp[ind][lft][f] = ret;
}

int main() {
    cin >> n;
    scanf("%d", &k);

    if (k == 0) {
        printf("1\n");
        return 0;
    }

    memset(dp, -1, sizeof dp);

    ll ans = 0;
    for (int i = 1; i <= 1000; i++) {
        ll aux = solve(0, i, 0);
        if (i == 1) { aux--; aux += MOD; aux %= MOD; }

        int op = k-1, x = i;
        while (x != 1) {
            x = __builtin_popcount(x);
            op--;
        }
        if (op == 0) {
            ans += aux;
            ans %= MOD;
        }
    }
    printf("%lld\n", ans);

    return 0;
}
