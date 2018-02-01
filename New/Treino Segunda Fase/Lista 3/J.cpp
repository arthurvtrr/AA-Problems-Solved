#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define EPS 1e-6

int n;

struct t {
    double i, d, h;
} ts[1010];

struct point {
    double x, y;
    point(double x, double y) : x(x), y(y) {}
};

bool cmp(t a, t b) {
    return a.i < b.i;
}

int main() {
    while (1) {
        scanf("%d", &n);
        if (n == -1) break;

        for (int i = 0; i < n; i++)
            scanf("%lf %lf %lf", &ts[i].i, &ts[i].d, &ts[i].h);

        sort(ts, ts+n, cmp);

        vector < point > pol;
        pol.push_back(point(ts[0].i, 0));
        pol.push_back(point((ts[0].i + ts[0].d) / 2, ts[0].h));
        pol.push_back(point(ts[0].d, 0));

        for (int i = 1; i < n; i++) {

        }

        printf("%f\n", ans);
    }
    return 0;
}
