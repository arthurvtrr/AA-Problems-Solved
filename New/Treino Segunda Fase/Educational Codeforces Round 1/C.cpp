#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-9
#define PI acos(-1)

int cmp(long double x, long double y = 0, long double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point {
    long double x, y;
    int ind;
    point(long double x = 0, long double y = 0, int ind = 0) : x(x), y(y), ind(ind) {}

    point operator -(point q) { return point(x - q.x, y - q.y); }
    long double operator *(point q) { return x * q.x + y * q.y; }
    long double operator %(point q) { return x * q.y - y * q.x; }

    int cmp(point q) const {
        if (int t = ::cmp(x, q.x)) return t;
        return ::cmp(y, q.y);
    }
};

long double angle(point p, point q, point r) {
    point u = p - q, v = r - q;
    return atan2(u % v, u * v);
}

bool radial_lt(point P, point Q) {
    return angle(P, point(), point(100000, 0)) < angle(Q, point(), point(100000, 0));
}

int n, x, y;
vector < point > ps;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        ps.push_back(point(x, y, i+1));
    }
    sort(ps.begin(), ps.end(), radial_lt);

    int best = 0;
    long double mini = DBL_MAX;
    for (int i = 0; i < n; i++) {
        long double a = abs(angle(ps[i], point(), ps[(i+1) % n]));
        if (a < mini) {
            best = i;
            mini = a;
        }
    }

    printf("%d %d\n", ps[best].ind, ps[(best+1) % n].ind);
    return 0;
}
