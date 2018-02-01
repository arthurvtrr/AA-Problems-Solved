#include <bits/stdc++.h>

using namespace std;

int n;

long double m, b;
map < long double, long double > minb, maxb;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%Lf %Lf", &m, &b);
        if (!minb.count(m)) minb[m] = maxb[m] = b;
        else {
            minb[m] = min(minb[m], b);
            maxb[m] = max(maxb[m], b);
        }
    }

    long double minx = LDBL_MAX, maxx = LDBL_MIN, miny = LDBL_MAX, maxy = LDBL_MIN;

    auto i = minb.begin();
    auto j = ++minb.begin();

    while (j != minb.end()) {
        long double b1[] = {minb[i->first], maxb[i->first]};
        long double b2[] = {minb[j->first], maxb[j->first]};

        for (int a = 0; a < 2; a++)
            for (int b = 0; b < 2; b++) {
                long double x = (b1[a] - b2[b]) / (i->first - j->first);
                long double y = i->first * x - b1[a];

                minx = min(minx, x);
                maxx = max(maxx, x);
                miny = min(miny, y);
                maxy = max(maxy, y);
            }

        i++; j++;
    }

    printf("%.5Lf %.5Lf %.5Lf %.5Lf\n", minx, miny, maxx, maxy);

    return 0;
}
