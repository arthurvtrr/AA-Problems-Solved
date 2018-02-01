#include <bits/stdc++.h>

using namespace std;

const int N = 300100;

int a[N], pref[N];
bool valid[N];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n + 1);

    int ini = 0, fim = 1000000000;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;

        memset(valid, 0, sizeof valid);
        memset(pref, 0, sizeof pref);

        int p = 1;
        while (p <= n && a[p] - a[1] <= meio) {
            if (p >= k) {
                valid[p] = true;
                pref[p] = 1;
            }
            pref[p] += pref[p-1];
            p++;
        }

        int l = 1;
        for (int i = p; i <= n; i++) {
            while (a[i] - a[l] > meio) l++;
            if (i - l + 1 >= k && pref[i-k] - (l == 1? 0 : pref[l-2]) > 0) {
                valid[i] = true;
                pref[i] = 1;
            }
            pref[i] += pref[i-1];
        }

        if (!valid[n]) ini = meio+1;
        else fim = meio-1;
    }

    printf("%d\n", fim+1);

    return 0;
}
