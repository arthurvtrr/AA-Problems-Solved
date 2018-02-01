#include <bits/stdc++.h>

using namespace std;

int q, x, y;

#define ll long long
#define MOD 1000000007

ll pow2[1001000], fat[1001000], inv[1001000];

bool prime[1001000];
vector < int > primes;

void sieve() {
    for (int i = 2; i < 1001000; i++)
        prime[i] = true;

    for (int i = 2; i < 1001000; i++)
        if (prime[i]) {
            primes.push_back(i);
            for (int j = 2*i; j < 1001000; j += i)
                prime[j] = false;
        }
}

ll mod(ll a, ll b) {
    return ((a%b)+b)%b;
}

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
    sieve();

    pow2[0] = fat[0] = 1;
    for (int i = 1; i < 1001000; i++) {
        pow2[i] = pow2[i-1] * 2;
        pow2[i] %= MOD;
        fat[i] = fat[i-1] * i;
        fat[i] %= MOD;
    }

    for (int i = 0; i < 1001000; i++)
        inv[i] = mod_inverse(fat[i], MOD);

    scanf("%d", &q);
    while (q--) {
        scanf("%d %d", &x, &y);
        ll ans = pow2[y-1];

        vector < int > quant;
        ll aux = x, total = 0;
        for (int i = 0; i < primes.size(); i++) {
            if (primes[i] * primes[i] > aux) break;
            int cnt = 0;
            while (aux % primes[i] == 0) {
                aux /= primes[i];
                cnt++;
            }
            quant.push_back(cnt);
            total += cnt;
        }
        if (aux != 1) {
            total++;
            quant.push_back(1);
        }

        for (int v : quant) {
            ll add = fat[v + y - 1];
            add *= inv[y-1];
            add %= MOD;
            add *= inv[v];
            add %= MOD;
            ans *= add;
            ans %= MOD;
        }

        printf("%lld\n", ans);
    }
    return 0;
}

