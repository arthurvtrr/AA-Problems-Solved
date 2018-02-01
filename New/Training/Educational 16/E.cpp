#include <bits/stdc++.h>

using namespace std;

#define INF LLONG_MAX
#define ll long long
#define pll pair < ll, int >

int n;
ll dp[20000200], x, y;

int main() {
    scanf("%d %lld %lld", &n, &x, &y);

    for (int i = 1; i < 20000200; i++)
        dp[i] = INF;

    dp[1] = x;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + x;
        if (i % 2 == 0) dp[i] = min(dp[i], dp[i/2] + y);
        else dp[i] = min(dp[i], dp[(i+1)/2] + x + y);
    }

    printf("%lld\n", dp[n]);

    return 0;
}

