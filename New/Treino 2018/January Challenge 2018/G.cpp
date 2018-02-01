#include <bits/stdc++.h>

using namespace std;

int t, x, n;
map < int, int > dp[33][1000010];
string s;

int solve(int ind, int lft, int acum) {
    if (dp[ind][lft].count(acum)) return dp[ind][lft][acum];
    if (ind == n-1) return (lft + acum == x? 0 : 1000);

    int ret = 1000;

    if (acum + lft <= x) ret = min(ret, (s[ind] != '0') + solve(ind+1, lft, acum + lft));
    if (1 + acum + lft <= x) ret = min(ret, (s[ind] != '1') + solve(ind+1, 1 + lft + acum, acum));

    return dp[ind][lft][acum] = ret;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        cin >> s;
        n = s.size();
        scanf("%d", &x);

        int ans = solve(1, 1, 0);
        if (ans != 1000) printf("YES\n%d\n", ans);
        else printf("NO\n");

        for (int i = 0; i <= s.size(); i++)
            for (int j = 0; j <= x; j++)
                dp[i][j].clear();
    }
    return 0;
}
