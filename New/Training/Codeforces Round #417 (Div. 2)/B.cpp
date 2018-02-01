#include <bits/stdc++.h>

using namespace std;

int n, m, dp[20][2], lfloor;
char grid[20][110];

int solve(int l, int lft) {
    if (dp[l][lft] != -1) return dp[l][lft];

    int x = 0, y = 0;
    for (int i = 0; i < m+2; i++)
        if (grid[l][i] == '1')
            x = i;

    for (int i = m+1; i >= 0; i--)
        if (grid[l][i] == '1')
            y = m - i + 1;

    int ret;

    if (l <= lfloor) {
        if (lft) ret = x;
        else ret = y;
    }
    else {
        if (lft) ret = 1 + min(solve(l-1, lft) + 2 * x, solve(l-1, 1 - lft) + m + 1);
        else ret = 1 + min(solve(l-1, lft) + 2 * y, solve(l-1, 1 - lft) + m + 1);
    }

    return dp[l][lft] = ret;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", grid[i]);

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < m+2; j++)
            if (grid[i][j] == '1')
                found = true;

        if (found) break;
        lfloor = i+1;
    }

    for (int i = 0; i < 20; i++)
        dp[i][0] = dp[i][1] = -1;

    printf("%d\n", solve(n-1, 1));

    return 0;
}

