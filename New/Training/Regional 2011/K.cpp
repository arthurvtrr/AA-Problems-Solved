#include <bits/stdc++.h>

using namespace std;

int n, dp[10100][10][2];
string s;

int solve(int ind, int d, int p) {
    printf("%d %d %d\n", ind, d, p);

    if (dp[ind][d][p] != -1) return dp[ind][d][p];
    if (ind == n) return false;
    if (s[ind] == 'X') return solve(ind+1, 1, p);
    if (d < 3) return solve(ind+1, d+1, p);

    bool ret = true;

    for (int i = ind; i < min(n, ind+3); i++) {
        bool valid = true;
        for (int j = i; j < min(n, i+3); j++)
            if (s[j] == 'X')
                valid = false;

        if (valid) ret &= solve(i+1, 1, 1 - p);
        else {
            if (i == ind) ret &= !solve(ind+1, d+1, p);
            break;
        }
    }

    return dp[ind][d][p] = !ret;
}

int main() {
    while (scanf("%d", &n), n) {
        cin >> s;
        bool win = false;

        for (int i = 0; i < s.size()-2; i++)
            if (s[i] == 'X' && (s[i+1] == 'X' || s[i+2] == 'X'))
                win = true;

        if (win) printf("S\n");
        else {
            memset(dp, -1, sizeof dp);
            if (solve(0, 3, 0)) printf("S\n");
            else printf("N\n");
        }
    }
    return 0;
}
