#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ldouble long double

int t;
ll n;

ll mul_mod(ll a, ll b, ll m) {
    ll y = (ll)((ldouble)a*(ldouble)b/m+(ldouble)1/2); y = y*m;
    ll x = a*b, r = x - y;
    if ((ll) r < 0) { r = r + m; y = y - 1; }
    return r;
}

ll exp_mod(ll a, ll e, ll mod) {
    if (e == 0) return 1;
    ll b = exp_mod(a, e/2, mod);
    return (e%2 == 0)? mul_mod(b, b, mod) : mul_mod(a, mul_mod(b, b, mod), mod);
}

ll llrand() {
    ll a = rand(); a <<= 32; a += rand(); return a;
}

bool is_probably_prime(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;

    ll s = 0, d = n - 1;
    while (d % 2 == 0) {
        d /= 2; s++;
    }

    for (int k = 0; k < 64; k++) {
        ll a = (llrand()%(n - 3)) + 2;
        ll x = exp_mod(a, d, n);
        if (x != 1 && x != n-1) {
            for (int r = 1; r < s; r++) {
                x = mul_mod(x, x, n);
                if (x == 1) return false;
                if (x == n-1) break;
            }
            if (x != n-1) return false;
        }
    }
    return true;
}

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%lld", &n);

        if (n <= 2) printf("2\n");
        else {
            for (int i = 0; i < 1000; i++)
                if ((n+i) % 2 == 1 && is_probably_prime(n+i)) {
                    printf("%lld\n", n+i);
                    break;
                }
        }
    }

    return 0;
}

