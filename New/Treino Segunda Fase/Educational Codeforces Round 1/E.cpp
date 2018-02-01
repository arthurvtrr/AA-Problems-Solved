#include <bits/stdc++.h>

using namespace std;

int t, n, m, k;
int dp[33][33][55];

int solve(int a, int b, int lft) {
    if (dp[a][b][lft] != -1) return dp[a][b][lft];
    if (lft == a*b) return 0;

    int ret = 10000000;
    for (int i = 1; i < a; i++) {
        for (int j = 1; j < lft; j++) {
            ret = min(ret, solve(i, b, j) + solve(a-i, b, lft-j) + b*b);
        }

        if (i*b >= lft) {
            ret = min(ret, solve(i, b, lft) + b*b);
            if ((a-i)*b < lft) ret = min(ret, solve(i, b, lft - (a-i)*b) + b*b);
        }
        if ((a-i)*b >= lft) {
            ret = min(ret, solve(a-i, b, lft) + b*b);
            if (i*b < lft) ret = min(ret, solve(a-i, b, lft - i*b) + b*b);
        }
    }

    for (int i = 1; i < b; i++) {
        for (int j = 1; j < lft; j++) {
            ret = min(ret, solve(a, i, j) + solve(a, b-i, lft-j) + a*a);
        }

        if (a*i >= lft) {
            ret = min(ret, solve(a, i, lft) + a*a);
            if (a*(b-i) < lft) ret = min(ret, solve(a, i, lft - a*(b-i)) + a*a);
        }
        if (a*(b-i) >= lft) {
            ret = min(ret, solve(a, b-i, lft) + a*a);
            if (a*i < lft) ret = min(ret, solve(a, b-i, lft - a*i) + a*a);
        }
    }

    return dp[a][b][lft] = ret;
}

int main() {
    memset(dp, -1, sizeof dp);

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d %d %d", &n, &m, &k);
        printf("%d\n", solve(n, m, k));
    }

    return 0;
}

