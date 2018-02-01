#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll n, k;
string lim;
ll dp[50][2][2];

ll solve(int ind, int l, int f) {
    if (dp[ind][l][f] != -1) return dp[ind][l][f];
    if (ind == n) return 1;

    ll ret = 0;
    if (f || lim[ind] == '1') {
        if (!l) ret += solve(ind+1, true, f);
        ret += solve(ind+1, false, true);
    }
    else ret += solve(ind+1, false, f);

    return dp[ind][l][f] = ret;
}

int main() {
    scanf("%lld %lld", &n, &k);

    ll ini = 0, fim = (1LL << n) - 1;
    while (ini <= fim) {
        ll meio = (ini + fim) / 2;
        memset(dp, -1, sizeof dp);

        lim = "";
        for (int i = n-1; i >= 0; i--) {
            if (meio & (1LL << i)) lim += '1';
            else lim += '0';
        }

        ll aux = solve(0, 0, 0);
        if (aux >= k) fim = meio-1;
        else ini = meio+1;
    }

    string ans = "";
    for (int i = n-1; i >= 0; i--) {
        if (ini & (1LL << i)) ans += '1';
        else ans += '0';
    }
    cout << ans << endl;

    return 0;
}
