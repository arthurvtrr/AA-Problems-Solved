#include <bits/stdc++.h>

using namespace std;

int n, x, pw2[10];
double prob[70][70], win[70][7];
double dp[70][70][7];

double solve(int ini, int fim, int l) {
    if (dp[ini][fim][l] > -0.5) return dp[ini][fim][l];

    double ret = 0.0;
    for (int i = ini; i <= fim; i++) {
        double aux = 0.0;

        for (int j = 0; j <= l; j++)
            aux += win[i][j] * pw2[j];

        for (int j = 1; j <= l; j++) {
            if (i % pw2[j+1] < pw2[j])
                aux += solve((i / pw2[j] + 1) * pw2[j], (i / pw2[j] + 1) * pw2[j] + pw2[j], j-1);
            else
                aux += solve((i / pw2[j] - 1) * pw2[j], (i / pw2[j] - 1) * pw2[j] + pw2[j], j-1);
        }

        ret = max(ret, aux);
    }
    return dp[ini][fim][l] = ret;
}

int main() {
    pw2[0] = 1;
    for (int i = 1; i < 10; i++)
        pw2[i] = pw2[i-1] * 2;

    scanf("%d", &n);
    for (int i = 0; i < pw2[n]; i++)
        for (int j = 0; j < pw2[n]; j++) {
            scanf("%d", &x);
            prob[i][j] = x / 100.0;
        }

    for (int i = 0; i < pw2[n]; i++) {
        if (i % 2 == 0) win[i][0] = prob[i][i+1];
        else win[i][0] = prob[i][i-1];
    }

    for (int i = 0; i < pw2[n]; i++)
        for (int j = 1; j < n; j++) {
            if (i % pw2[j+1] < pw2[j]) {
                int ini = (i / pw2[j] + 1) * pw2[j];

                for (int k = 0; k < pw2[j]; k++)
                    win[i][j] += win[i][j-1] * win[ini + k][j-1] * prob[i][ini + k];
            }
            else {
                int ini = (i / pw2[j] - 1) * pw2[j];

                for (int k = 0; k < pw2[j]; k++)
                    win[i][j] += win[i][j-1] * win[ini + k][j-1] * prob[i][ini + k];
            }
        }

    for (int i = 0; i < 70; i++)
        for (int j = 0; j < 70; j++)
            for (int k = 0; k < 7; k++)
                dp[i][j][k] = -1.0;

    printf("%f\n", solve(0, pw2[n]-1, n-1));

    return 0;
}

