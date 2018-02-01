#include <bits/stdc++.h>

using namespace std;

int t, n, k, grid[9][9], aux[9][9];
int vert[17][9], hor[17][9];
double propg, propv, proph, dv;

void rotate_hor(int x, int y) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            aux[j][n-i-1] = hor[i+x][j+y];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            hor[i+x][j+y] = aux[i][j];
}

int dp[17][9][260][35];

int solve(int row, int col, int mask, int quant, int type) {
    if (dp[row][col][mask][quant] != -1)
        return dp[row][col][mask][quant];

    int& ret = dp[row][col][mask][quant];
    ret = 0;

    if (col == n) return ret = solve(row+1, 0, mask, quant, type);
    if (row == n && type == 0) return ret = (quant == 0);
    if (row == 2*n) return ret = (quant == 0);
    if (mask & (1 << col)) return ret = solve(row, col+1, mask ^ (1 << col), quant, type);

    if (type == 2) {
        if (quant > 0 && col+1 < n && !(mask & (1 << (col+1))))
            ret += solve(row, col+2, mask, quant-1, type);
        if (row+1 < n)
            ret += solve(row, col+1, mask | (1 << col), quant, type);
    }
    else {
        if (col+1 < n && !(mask & (1 << (col+1))))
            ret += solve(row, col+2, mask, quant, type);
        if (row+1 < n && quant > 0)
            ret += solve(row, col+1, mask | (1 << col), quant-1, type);
    }

    return ret;
}

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        int np = 0;

        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                scanf("%d", &grid[i][j]);
                if (grid[i][j] == 0) np++;
            }
        np /= 2;

        for (int i = 0; i < 2*n; i++)
            for (int j = 0; j < n; j++)
                vert[i][j] = hor[i][j] = grid[i%n][j];

        rotate_hor(0, 0);
        rotate_hor(n, 0);

        propg = dv = 0.0;
        memset(dp, -1, sizeof(dp));

        for (int i = 0; i <= 35; i++) {
            int x = solve(0, 0, 0, i, 0);
            propg += x * i;
            dv += x;
        }
        propg /= dv * np;

        propv = dv = 0.0;
        memset(dp, -1, sizeof(dp));

        for (int i = 0; i <= 35; i++) {
            int x = solve(0, 0, 0, i, 1);
            propv += x * i;
            dv += x;
        }
        propv /= dv * np * 2;

        proph = dv = 0.0;
        memset(dp, -1, sizeof(dp));

        for (int i = 0; i <= n*n/2; i++) {
            int x = solve(0, 0, 0, i, 2);
            proph += x * i;
            dv += x;
        }
        proph /= dv * np * 2;

        printf("%f %f %f\n", propg, propv, proph);
    }

    return 0;
}
