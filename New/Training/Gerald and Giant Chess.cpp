#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define pii pair < int, int >
#define ll long long

int h, w, n;
pii cells[2020];
ll fat[200200];

ll mod(ll a, ll b) { return ((a%b)+b)%b; }

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

ll comb(ll a, ll b) {
    return (fat[a] * mod_inverse((fat[a-b] * fat[b]) % MOD, MOD)) % MOD;
}

ll dp[2020];

int main() {
    scanf("%d %d %d", &h, &w, &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &cells[i].first, &cells[i].second);
    cells[n] = pii(1, 1);
    cells[n+1] = pii(h, w);
    sort(cells, cells+n+2);

    fat[0] = 1;
    for (int i = 1; i < 200200; i++) {
        fat[i] = i * fat[i-1];
        fat[i] %= MOD;
    }

    ll total = comb(h+w-2, h-1);

    dp[0] = 1;

    for (int i = 1; i < n+2; i++) {
        for (int j = 1; j < i; j++) {
            int a = cells[i].first, b = cells[j].first, c = cells[i].second, d = cells[j].second;
            if (a < b || c < d)  continue;

            dp[i] += mod(comb(b+d-2, b-1) - dp[j], MOD) * comb(a - b + c - d, a - b);
            dp[i] = mod(dp[i], MOD);
        }
    }

    printf("%lld\n", mod(total - dp[n+1], MOD));

    return 0;
}
