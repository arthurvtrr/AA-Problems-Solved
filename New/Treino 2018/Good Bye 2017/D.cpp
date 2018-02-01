#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007

ll k, a, b, dp[100][1000][100];

ll solve(int siz, int ind, int qa) {
    if (dp[siz][ind][qa] != -1) return dp[siz][ind][qa];
    if (ind >= k) return ind;
    if (qa == k) return 1;
    if (siz > 90) return 0;

    ll ret = 0;
    ret += a * solve(siz+1, ind, qa+1);
    ret %= MOD;
    ret += b * solve(siz+1, ind+qa, qa);
    ret %= MOD;

    return dp[siz][ind][qa] = ret;
}

ll fpow(ll base, ll exp) {
    if (exp == 1) return base;
    ll ret = fpow(base, exp/2);
    ret *= ret; ret %= MOD;
    if (exp % 2) ret *= base;
    return ret % MOD;
}

int main() {
    scanf("%lld %lld %lld", &k, &a, &b);
    memset(dp, -1, sizeof dp);
    printf("%lld\n", (solve(0, 0, 0) ) % MOD);
    return 0;
}
