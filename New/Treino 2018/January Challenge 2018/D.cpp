#include <bits/stdc++.h>

using namespace std;

int t, n, m, nxta[5050], nxtb[5050], dp[5050][5050];
string a, b;

int solve(int x, int y) {
    if (dp[x][y] != -1) return dp[x][y];
    if (x == n && y == m) return 0;
    if (x == n) return dp[x][y] = 1 + solve(x, nxtb[y]);
    if (y == m) return dp[x][y] = 1 + solve(nxta[x], y);

    int ret = 100000000;
    if (a[x] == b[y]) ret = 1 + solve(nxta[x], nxtb[y]);
    ret = min(ret, 1 + solve(nxta[x], y));
    ret = min(ret, 1 + solve(x, nxtb[y]));

    return dp[x][y] = ret;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        cin >> a; cin >> b;

        int aux = n;
        nxta[n-1] = aux;
        for (int i = n-2; i >= 0; i--) {
            if (a[i] != a[i+1]) aux = i+1;
            nxta[i] = aux;
        }

        aux = m;
        nxtb[m-1] = aux;
        for (int i = m-2; i >= 0; i--) {
            if (b[i] != b[i+1]) aux = i+1;
            nxtb[i] = aux;
        }

        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                dp[i][j] = -1;

        printf("%d\n", solve(0, 0));
    }
    return 0;
}
