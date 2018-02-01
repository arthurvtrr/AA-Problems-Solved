#include <bits/stdc++.h>

using namespace std;

int m, n, k;
string a, b;

#define N 1000100
#define M 110

int dp[N][M];

int main() {
    scanf("%d %d %d", &m, &n, &k);
    cin >> a >> b;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            dp[i][j] = 63;

    for (int i = 0; i < n; i++)
        dp[i][0] = 0;

    for (int i = 0; i < N-1; i++)
        for (int j = 0; j < M-1; j++) {
            dp[i][j+1] = min(dp[i][j+1], dp[i][j] + 1);
            dp[i+1][j] = min(dp[i+1][j], dp[i][j] + 1);
            if (i < n && j < m) dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + (a[j] != b[i]));
        }

    bool valid = false;
    for (int i = 0; i < N; i++)
        if (dp[i][m] <= k)
            valid = true;

    if (valid) printf("S\n");
    else printf("N\n");

    return 0;
}
