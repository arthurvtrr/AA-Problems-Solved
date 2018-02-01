#include <bits/stdc++.h>

using namespace std;

#define MOD 7340033
#define ll long long

int q, n, k;
ll dp[1010][35], quant[5] = {0, 4, 6, 4, 1};

int main() {
    for (int i = 0; i < 35; i++) dp[0][i] = 1;

    for (int i = 1; i < 1010; i++) {
        for (int j = 1; j < 35; j++) {
            for (int k = 1; k <= min(i, 4); k++) {
                dp[i][j] += quant[k] * dp[i - k][j-1];
                dp[i][j] %= MOD;
            }
        }
    }

    for (int i = 0; i < 150; i++) {
        printf("left %d\n", i);
        for (int j = 0; j < 6; j++)
            printf("%lld ", dp[i][j]);
        printf("\n");
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &n, &k);
        if (k == 0) printf("1\n");
        else if (n == 1 || n % 2 == 0) printf("0\n");
        else {
            int lvl = 0, aux = n;
            while (aux >= 7 && aux % 2) {
                lvl++;
                aux /= 2;
            }
            printf("%d\n", lvl);
            printf("%lld\n", dp[k-1][lvl]);
        }
    }

    return 0;
}
