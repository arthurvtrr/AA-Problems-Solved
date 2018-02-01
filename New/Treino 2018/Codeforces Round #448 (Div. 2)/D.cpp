#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007

string a, b;
ll fact[1001000], invf[1001000];

ll fastPow(ll base, ll exp) {
    if (exp == 1) return base;
    ll ret = fastPow(base, exp/2);
    ret *= ret; ret %= MOD;
    if (exp % 2) ret *= base;
    return ret % MOD;
}

int cnt[30];

ll solve(string s) {
    for (int i = 0; i < 30; i++) cnt[i] = 0;
    for (int i = 0; i < a.size(); i++) cnt[a[i] - 'a']++;

    ll ret = 0, aux = fact[a.size()];
    for (int i = 0; i < 30; i++) {
        if (cnt[i] == 0) continue;
        aux *= invf[cnt[i]];
        aux %= MOD;
    }

    for (int i = 0; i < s.size(); i++) {
        aux *= invf[(int)a.size() - i]; aux %= MOD;
        aux *= fact[(int)a.size() - i - 1]; aux %= MOD;

        for (int j = 0; j < (s[i] - 'a'); j++) {
            ret += (aux * cnt[j]) % MOD;
            ret %= MOD;
        }

        if (cnt[s[i] - 'a'] == 0) break;

        aux *= cnt[s[i] - 'a']; aux %= MOD;
        cnt[s[i] - 'a']--;
    }

    return ret;
}

int main() {
    cin >> a >> b;

    fact[0] = 1;
    for (int i = 1; i < 1001000; i++) {
        fact[i] = fact[i-1] * i;
        fact[i] %= MOD;
        invf[i] = fastPow(fact[i], MOD - 2);
    }

    printf("%lld\n", (solve(b) - solve(a) - 1 + MOD) % MOD);

    return 0;
}
