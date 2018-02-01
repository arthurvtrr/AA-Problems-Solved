#include <bits/stdc++.h>

using namespace std;

struct point {
    long long x, y;
    point(long long x, long long y) : x(x), y(y) {}
};

int n, m, k, a, b;
vector < point > pol;

long long areaTriangle(const point &a, const point &b, const point &c) {
    return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

bool inConvexPoly(const vector < point > &convPoly, point p) {
    long long start = 1, last = (int) convPoly.size() - 1;
    while (last - start > 1) {
        long long mid = (start + last) / 2;
        if (areaTriangle(convPoly[0], convPoly[mid], p) < 0) last = mid;
        else start = mid;
    }

    long long r0 = abs(areaTriangle(convPoly[0], convPoly[start], convPoly[last]));
    long long r1 = abs(areaTriangle(convPoly[0], convPoly[start], p));
    long long r2 = abs(areaTriangle(convPoly[0], convPoly[last], p));
    long long r3 = abs(areaTriangle(convPoly[start], convPoly[last], p));

    return r0 == (r1 + r2 + r3);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        pol.push_back(point(a, b));
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        if (inConvexPoly(pol, point(a, b))) k--;
    }

    if (k <= 0) printf("YES\n");
    else printf("NO\n");

    return 0;
}
