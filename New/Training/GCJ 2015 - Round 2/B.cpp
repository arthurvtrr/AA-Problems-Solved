#include <bits/stdc++.h>

using namespace std;

const long double EPS = 1e-14;

int t, n;
long double v, x;

struct source {
    long double r, c;
} srcs[110];

bool cmp(source a, source b) {
    return a.c < b.c;
}

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d %Lf %Lf", &n, &v, &x);
        for (int i = 0; i < n; i++)
            scanf("%Lf %Lf", &srcs[i].r, &srcs[i].c);

        sort(srcs, srcs+n, cmp);

        long double temp = 0.0, dv = 0.0;
        for (int i = 0; i < n; i++) {
            temp += srcs[i].r * srcs[i].c;
            dv += srcs[i].r;
        }
        temp /= dv;

        if (fabs(temp - x) < EPS) printf("Case #%d: %.9Lf\n", tc, v / dv);
        else if (temp < x) {
            bool found = false;
            for (int i = 0; i < n; i++) {
                long double aux = 0.0, auxd = 0.0;
                for (int j = i+1; j < n; j++) {
                    aux += srcs[j].r * srcs[j].c;
                    auxd += srcs[j].r;
                }
                aux /= auxd;

                if (aux + EPS > x) {
                    long double ini = 0.0, fim = srcs[i].r, val, d;
                    while (fabs(ini - fim) > EPS) {
                        long double mid = (ini + fim) / 2;
                        val = mid * srcs[i].c; d = mid;

                        for (int j = i+1; j < n; j++) {
                            val += srcs[j].r * srcs[j].c;
                            d += srcs[j].r;
                        }

                        if (val / d > x) ini = mid;
                        else fim = mid;
                    }

                    printf("Case #%d: %.9Lf\n", tc, v / d);
                    found = true;
                    break;
                }
            }
            if (!found) printf("Case #%d: IMPOSSIBLE\n", tc);
        }
        else {
            bool found = false;
            for (int i = n-1; i >= 0; i--) {
                long double aux = 0.0, auxd = 0.0;
                for (int j = i-1; j >= 0; j--) {
                    aux += srcs[j].r * srcs[j].c;
                    auxd += srcs[j].r;
                }
                aux /= auxd;

                if (aux < x + EPS) {
                    long double ini = 0.0, fim = srcs[i].r, val, d;
                    while (fabs(ini - fim) > EPS) {
                        long double mid = (ini + fim) / 2;
                        val = mid * srcs[i].c; d = mid;

                        for (int j = i-1; j >= 0; j--) {
                            val += srcs[j].r * srcs[j].c;
                            d += srcs[j].r;
                        }

                        if (val / d > x) fim = mid;
                        else ini = mid;
                    }

                    printf("Case #%d: %.9Lf\n", tc, v / d);
                    found = true;
                    break;
                }
            }
            if (!found) printf("Case #%d: IMPOSSIBLE\n", tc);
        }
    }

    return 0;
}

