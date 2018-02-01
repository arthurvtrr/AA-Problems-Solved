#include <bits/stdc++.h>

using namespace std;

string s;

#define MOD 1000000007
#define ll long long

ll fastPow(ll base, ll exp) {
    if (exp < 1) return 1;
    ll ret = fastPow(base, exp/2);
    ret *= ret; ret %= MOD;
    if (exp % 2) ret *= base;
    return ret % MOD;
}

int main() {
    cin >> s;

    ll ans = 0, acont = 0, bcont = 0;
    for (int i = s.size()-1; i >= 0; i--) {
        if (s[i] == 'a') acont++;
        else ans += fastPow(2, acont) - 1;
        ans %= MOD;
    }
    printf("%lld\n", ans);

    return 0;
}
