#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007

int n, nums[220000];
ll cnt[1000100], dp[1000100];

ll f(int n) {
    ll ret = 0;
    for (int i = 1; i < 1 << n; i++)
        ret += __builtin_popcount(i);
    printf("%d %lld\n", n, ret);
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        cnt[nums[i]]++;
    }

    memset(dp, -1, sizeof(dp));

    ll ans = 0;
    for (int i = 1000000; i > 1; i--) {
        if (cnt[i] == 0) continue;

        ll sum = 0;
        for (int j = 2*i; j <= 1000000; j += i)
            sum += cnt[j];

        ll add = (f(sum) + 1) * f(cnt[i]);
        add %= MOD;
        ans += add * i;
        ans %= MOD;
    }
    printf("%lld\n", ans);

    return 0;
}

