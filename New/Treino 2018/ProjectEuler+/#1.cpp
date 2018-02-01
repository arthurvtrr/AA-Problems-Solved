#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t;
ll n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        n--;

        ll ans = n/3 * (n/3 + 1) / 2 * 3;
        ans += n/5 * (n/5 + 1) / 2 * 5;
        ans -= n/15 * (n/15 + 1) / 2 * 15;
        printf("%lld\n", ans);
    }
    return 0;
}
