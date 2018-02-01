#include <bits/stdc++.h>

using namespace std;

int rh, rv, sh, sv;
int n;

struct screen {
    int a, b, c, d, e;
} s[110];

int iceil(int a, int b) {
    return (a + b - 1) / b;
}

int main() {
    freopen("giant.in", "r", stdin);
    freopen("giant.out", "w", stdout);

    scanf("%d %d %d %d", &rh, &rv, &sh, &sv);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d %d", &s[i].a, &s[i].b, &s[i].c, &s[i].d, &s[i].e);
    }

    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        ans = min(ans, max(iceil(rh, s[i].a), iceil(sh, s[i].c))*max(iceil(rv, s[i].b), iceil(sv, s[i].d))*s[i].e);
        ans = min(ans, max(iceil(rh, s[i].b), iceil(sh, s[i].d))*max(iceil(rv, s[i].a), iceil(sv, s[i].c))*s[i].e);
    }
    printf("%d\n", ans);

    return 0;
}

