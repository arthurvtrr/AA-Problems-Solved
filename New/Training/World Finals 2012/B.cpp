#include <bits/stdc++.h>

using namespace std;

#define PI acos(-1)
#define EPS 1e-6

int n;
long double coefs[12], xl, xh, inc;

long double get_value(long double x) {
    long double ret = 0.0;
    for (int i = 0; i <= n; i++) {
        long double aux = 1.0;
        for (int j = 0; j < i; j++)
            aux *= x;
        ret += coefs[i] * aux;
    }
    ret *= ret * PI;
    return ret;
}

long double simpson(long double a, long double b) {
    long double sum = get_value(a) + get_value(b);
    int k = (int)1e4;
    long double h = (b-a)/(long double)k;
    for (int i = 1; i <= k; i += 2) sum += 4.0 * get_value(a + i*h);
    for (int i = 2; i <= k-1; i += 2) sum += 2.0 * get_value(a + i*h);
    return sum * h/3.0;
}

int main() {
    int t = 1;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i <= n; i++)
            scanf("%Lf", &coefs[i]);
        scanf("%Lf %Lf %Lf", &xl, &xh, &inc);

        long double vol = simpson(xl, xh);
        printf("Case %d: %.2Lf\n", t++, vol);

        bool found = false;
        for (int i = 1; i <= 8; i++) {
            long double need = inc * i, ini = xl, fim = xh;

            while (fabs(fim - ini) > EPS) {
                long double meio = (ini + fim) / 2;
                if (simpson(xl, meio) < need) ini = meio;
                else fim = meio;
            }

            if (fim < xh) {
                if (found) printf(" ");
                printf("%.2Lf", fim - xl);
                found = true;
            }
        }
        if (found) printf("\n");
        else printf("insufficient volume\n");
    }

    return 0;
}
