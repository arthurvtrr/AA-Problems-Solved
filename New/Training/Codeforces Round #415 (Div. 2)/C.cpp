#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

int n;
long long coords[300300], pow2[300300];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &coords[i]);
    sort(coords, coords+n);

    pow2[0] = 1;
    for (int i = 1; i < 300300; i++) {
        pow2[i] = pow2[i-1] * 2;
        pow2[i] %= MOD;
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (pow2[i] - 1) * coords[i];
        ans %= MOD;
        ans -= (pow2[n-i-1] - 1) * coords[i];
        ans %= MOD; ans += MOD; ans %= MOD;
    }
    printf("%lld\n", ans);

    return 0;
}
