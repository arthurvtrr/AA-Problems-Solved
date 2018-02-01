#include <bits/stdc++.h>

using namespace std;

int t, n, m, x, y;
long long val[303][303];
set < long long > dp[303][303];
string s;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d", &n);
        cin >> s;
        scanf("%d %d %d", &m, &x, &y);

        for (int i = 0; i < 303; i++)
            for (int j = 0; j < 303; j++) {
                val[i][j] = 0;
                dp[i][j].clear();
            }

        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
                if (j - i <= m + 3)
                    for (int k = i; k <= j; k++) {
                        val[i][j] *= 10;
                        val[i][j] += s[k] - '0';
                    }

        long long ans = 0;

        for (int i = 0; i < min(m, n); i++)
            dp[i][0].insert(val[0][i]);

        for (int i = 1; i < n; i++)
            for (int j = 1; j <= y; j++)
                for (int k = 1; k <= min(m, i); k++) {
                    if (dp[i-k][j-1].empty()) continue;
                    for (auto v : dp[i-k][j-1])
                        dp[i][j].insert(gcd(val[i-k+1][i], v));
                }

        for (int j = x; j <= y; j++)
            for (auto v : dp[n-1][j])
                ans = max(ans, v);

        printf("%lld\n", ans);
    }

    return 0;
}
