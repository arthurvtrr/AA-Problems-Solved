#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define AUX 2000000

int n;
ll x, y, nums[500500], cnt[2000200], sum[2000200];

int main() {
    scanf("%d %lld %lld", &n, &x, &y);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &nums[i]);
        cnt[nums[i]]++;
        sum[nums[i]] += AUX - nums[i];
    }

    for (int i = 1; i < 2000200; i++) {
        cnt[i] += cnt[i-1];
        sum[i] += sum[i-1];
    }

    ll ans = LLONG_MAX;
    for (ll i = 2; i <= 1000000; i++) {
        ll cost = 0, used = 0;
        for (ll j = i; j <= 1000000 + i; j += i) {
            ll atual = cnt[j] - cnt[max(j - x/y - 1, j - i)], asum = sum[j] - sum[max(j - x/y - 1, j - i)];
            asum -= (AUX - j) * atual;
            cost += asum * y;
            used += atual;
        }
        cost += (n - used) * x;

        ans = min(ans, cost);
    }

    printf("%lld\n", ans);

    return 0;
}
