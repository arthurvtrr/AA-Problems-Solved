#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll m, b;

int main() {
    scanf("%lld %lld", &m, &b);

    ll ans = 0;
    for (ll i = 0; i <= m*b; i++) {
        ll y = floor(i * -1.0 / m + b);
        ans = max(ans, (i * (i + 1) / 2) * (y+1) + (y * (y + 1) / 2) * (i+1));
    }
    printf("%lld\n", ans);

    return 0;
}

