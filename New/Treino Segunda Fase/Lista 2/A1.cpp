#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007
#define pii pair < int, int >

int n, x[1010], y[1010];
ll comb[1010][1010], ans[1010];
map < pii, int > cnt;
set < pii > points;

int main() {
    for (int i = 0; i < 1010; i++) {
        comb[i][0] = 1;
        comb[i][i] = 1;
    }

    for (int i = 1; i < 1010; i++)
        for (int j = 1; j < i; j++) {
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
            if (comb[i][j] > MOD) comb[i][j] -= MOD;
        }

    while (scanf("%d", &n) != EOF) {
        cnt.clear(); points.clear();
        for (int i = 1; i <= n; i++)
            ans[i] = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x[i], &y[i]);
            points.insert(pii(x[i], y[i]));
        }

        for (int i = 0; i < n; i++)
            for (int j = i+1; j < n; j++) {
                cnt[pii(x[i]+x[j], y[i]+y[j])]++;
            }

        for (map < pii, int >::iterator it = cnt.begin(); it != cnt.end(); it++) {
            pii aux = it->first;
            int q = it->second;
            bool valid = (aux.first & 1) == 0 && (aux.second & 1) == 0 && points.count(pii(aux.first/2, aux.second/2));

            for (int i = 1; i <= q; i++) {
                ans[2*i] += comb[q][i];
                if (ans[2*i] > MOD) ans[2*i] -= MOD;
                if (valid) {
                    ans[2*i+1] += comb[q][i];
                    if (ans[2*i+1] > MOD) ans[2*i+1] -= MOD;
                }
            }
        }

        ans[1] = n;
        for (int i = 1; i <= n; i++) {
            if (i > 1) printf(" ");
            printf("%lld", ans[i]);
        }
        printf("\n");
    }

    return 0;
}
