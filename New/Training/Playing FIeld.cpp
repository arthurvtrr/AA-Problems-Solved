#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

struct point {
    double x;
    double y;
} points[50500];

double area(point a, point b, point c) {
    vector < point > aux = {a, b, c, a};

    double ret = 0.0;
    for (int i = 0; i < 3; i++)
        ret += aux[i].x * aux[i+1].y - aux[i+1].x * aux[i].y;

    return fabs(ret) / 2.0;
}

int n, q, a, b;
double acum[50500];

int main() {
    int t = 0;
    while (scanf("%d %d", &n, &q)) {
        if (n + q == 0) break;

        if (t != 0) printf("\n");

        for (int i = 0; i < n; i++)
            scanf("%lf %lf", &points[i].x, &points[i].y);

        for (int i = 2; i < n; i++) {
            acum[i] = area(points[0], points[i-1], points[i]);
            acum[i] += acum[i-1];
        }

        for (int i = 0; i < q; i++) {
            scanf("%d %d", &a, &b);

            double aux = acum[b] - acum[a] - area(points[0], points[a], points[b]);
            if (aux > acum[n-1] - aux)
                aux = acum[n-1] - aux;

            printf("%.1f\n", aux);
        }
        t++;
    }

    return 0;
}
