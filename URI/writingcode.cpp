#include <bits/stdc++.h>

using namespace std;

int a[550];
int z[2][550][550];

int main() {
    int n, m, b, mod;
    scanf("%d %d %d %d", &n, &m, &b, &mod);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    z[0][0][0] = 1;

    for (int it = 1; it <= n; it++) {
        int i = it & 1;
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= b; k++) {
                z[i][j][k] = z[i ^ 1][j][k];
                if (j > 0 && k >= a[it - 1])
                    z[i][j][k] += z[i][j - 1][k - a[it - 1]];
                z[i][j][k] %= mod;
            }
        }
    }

    int s = 0;
    for (int i = 0; i <= b; i++) {
        s += z[n & 1][m][i];
        s %= mod;
    }
    printf("%d\n", s);

    return 0;
}
