#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll n, k;

int main() {
    scanf("%lld %lld", &n, &k);
    ll ans = (n / k + 1) * (n / k) / 2 * (n % k);
    ans += (n / k) * (n / k - 1) / 2 * (k - (n % k));
    printf("%lld\n", ans);

    return 0;
}
