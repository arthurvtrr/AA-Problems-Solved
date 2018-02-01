#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define INF 1000000000000000000

int n, m, ans[260];
ll C[260][260];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &C[i][j]);

    for (int i = 0; i < m; i++) {
        int best = 0;
        ll val = INF;
        for (int j = 0; j < n; j++) {
            ll aux = 0;
            for (int k = 0; k < n; k++) {
                ll atual = ans[j] - ans[k];
                aux += (2*atual + 1) * C[j][k];
                atual = ans[k] - ans[j];
                aux += (-2*atual + 1) * C[j][k];
            }
            if (aux <= val) {
                best = j;
                val = aux;
            }
        }
        ans[best]++;
    }

    for (int t = 0; t < 20; t++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                while (ans[i] > 0) {
                    ll change = 0;
                    for (int k = 0; k < n; k++) {
                        ll atual = ans[i] - ans[k];
                        change += (-2*atual + 1) * C[i][k];
                        atual = ans[k] - ans[i];
                        change += (2*atual + 1) * C[i][k];
                    }
                    for (int k = 0; k < n; k++) {
                        ll atual = ans[j] - ans[k];
                        change += (2*atual + 1) * C[j][k];
                        atual = ans[k] - ans[j];
                        change += (-2*atual + 1) * C[j][k];
                    }

                    if (change >= 0) break;
                    ans[i]--; ans[j]++;
                }
            }
    }

    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
