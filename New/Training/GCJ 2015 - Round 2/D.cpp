#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define ll long long

int t, r, c, ini, aux[3] = {3, 4, 6};
ll dp[110][10][3];

ll gcd(ll a, ll b) { return b == 0? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }

ll solve(int row, int p, int l3) {
	if (dp[row][p][l3] != -1) return dp[row][p][l3];
	if (row == r) return p == 0;

	ll ret = 0;

	if (l3 != 0) {
		ret += solve(row+1, p, 0);
		ret %= MOD;

		if (c % 3 == 0 && (ini & 1) && row < r - 1) {
			int np = (p & 1)? p - 1 : p;
			ret += solve(row+2, np, 0) * 3;
			ret %= MOD;
		}
		if (c % 4 == 0 && (ini & 2) && row < r - 2) {
			int np = (p & 2)? p - 2 : p;
			ret += solve(row+3, np, 0) * 4;
			ret %= MOD;
		}
		if (c % 6 == 0 && (ini & 4) && row < r - 1) {
			int np = (p & 4)? p - 4 : p;
			ret += solve(row+2, np, 0) * 6;
			ret %= MOD;
		}
	}
	if (l3 != 1 && row < r - 1) ret += solve(row+2, p, 1);

	return dp[row][p][l3] = ret % MOD;
}

ll mod(ll a, ll b) { return ((a % b) + b) % b; }

ll extended_euclid(ll a, ll b, ll &x, ll &y) {
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {
        ll q = a/b;
        ll t = b; b = a%b; a = t;
        t = xx; xx = x-q*xx; x = t;
        t = yy; yy = y-q*yy; y = t;
    }
    return a;
}

ll mod_inverse(ll a, ll n) {
    ll x, y;
    ll d = extended_euclid(a, n, x, y);
    if (d > 1) return -1;
    return mod(x, n);
}

int main() {
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d", &r, &c);
		ll ans = 0;
		for (int i = 0; i < 8; i++) {
			ll per = 1;
			for (int j = 0; j < 3; j++)
				if (i & (1 << j))
					per = lcm(per, aux[j]);

			ini = i;
			memset(dp, -1, sizeof dp);
			ans += solve(0, i, 2) * mod_inverse(per, MOD);
			ans %= MOD;
		}
		printf("Case #%d: %lld\n", tc, ans);
	}

	return 0;
}
