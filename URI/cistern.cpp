#include <stdio.h>
#include <math.h>

using namespace std;

struct cistern {
    int b, h, w, d;

    void set(int u, int x, int y, int z) {
        b = u, h = x, w = y, d = z;
    }

} cisterns[55000];

const double EPS = 1e-9;

double buscaResult(double x, int n) {
    double e, d;
    e = 0.0, d = 1100000.0;

    for (int j = 0; j < 50; j++) {
        double h = (e + d) / 2.0, v = 0.0;
        for (int i = 0; i < n; i++) {
            if (h - cisterns[i].b > 0)
                v += fmin(h - cisterns[i].b, cisterns[i].h) * cisterns[i].w * cisterns[i].d * 1.0;
        }
        if (v+EPS < x) e = h;
        else d = h;
    }

    return e;
}

int main() {
    int k, n, v;
    double a, b, c, d, amin, amax, vmax;
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        amin = -1, amax = 10000000, vmax = 0;
        scanf("%d", &n);
        for (int j = 0; j < n; j++) {
            scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
            cisterns[j].set(a, b, c, d);
            amin = fmin(amin, a);
            amax = fmax(amax, a+b);
            vmax += b*c*d;
        }
        scanf("%d", &v);

        if (vmax < v) printf("OVERFLOW\n");
        else {
            double s = buscaResult(v, n);
            printf("%.2f\n", s);
        }

    }
    return 0;
}
