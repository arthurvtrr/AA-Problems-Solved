#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007
#define pii pair < int, int >

int n, x[1010], y[1010];
ll comb[1010][1010], ans[1010];
vector < pii > cnt;
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

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
        points.insert(pii(x[i], y[i]));
    }

    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            cnt.push_back(pii(x[i]+x[j], y[i]+y[j]));

    if (n == 1) {
        printf("1\n");
        return 0;
    }

    sort(cnt.begin(), cnt.end());

    int quant = 1;
    for (int i = 1; i < cnt.size(); i++) {
        if (cnt[i] != cnt[i-1]) {
            bool valid = (cnt[i-1].first & 1) == 0 && (cnt[i-1].second & 1) == 0 && points.count(pii(cnt[i-1].first/2, cnt[i-1].second/2));

            for (int j = 1; j <= quant; j++) {
                ans[2*j] += comb[quant][j];
                if (ans[2*j] > MOD) ans[2*j] -= MOD;
                if (valid) {
                    ans[2*j+1] += comb[quant][j];
                    if (ans[2*j+1] > MOD) ans[2*j+1] -= MOD;
                }
            }
            quant = 1;
        }
        else quant++;
    }

    bool valid = (cnt.back().first & 1) == 0 && (cnt.back().second & 1) == 0 && points.count(pii(cnt.back().first/2, cnt.back().second/2));

    for (int j = 1; j <= quant; j++) {
        ans[2*j] += comb[quant][j];
        if (ans[2*j] > MOD) ans[2*j] -= MOD;
        if (valid) {
            ans[2*j+1] += comb[quant][j];
            if (ans[2*j+1] > MOD) ans[2*j+1] -= MOD;
        }
    }

    ans[1] = n;
    for (int i = 1; i <= n; i++) {
        if (i > 1) printf(" ");
        printf("%lld", ans[i]);
    }
    printf("\n");

    return 0;
}
