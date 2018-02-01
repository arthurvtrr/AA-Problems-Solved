#include <bits/stdc++.h>

using namespace std;

int n;
string s;
int dp[110][220][220];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int pos[300];

int solve(int ind, int x, int y) {
    if (dp[ind][x][y] != -1) return dp[ind][x][y];
    if (ind == n) {
        if (x == 100 && y == 100) return 0;
        return -1000;
    }

    int ret = -1000;
    ret = max(ret, solve(ind+1, x, y));
    ret = max(ret, 1 + solve(ind+1, x + dx[pos[s[ind]]], y + dy[pos[s[ind]]]));

    return dp[ind][x][y] = ret;
}

int main() {
    cin >> n >> s;
    memset(dp, -1, sizeof dp);
    pos['L'] = 0; pos['R'] = 1; pos['D'] = 2; pos['U'] = 3;
    printf("%d\n", solve(0, 100, 100));

    return 0;
}
