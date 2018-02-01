#include <bits/stdc++.h>

using namespace std;

#define polygon vector < point >
#define EPS 1e-9
#define PI acos(-1)

int n, x, y;

int cmp(double x, double y = 0) {
	return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
}

struct point {
	double x, y;
	point(double x = 0, double y = 0): x(x), y(y) {}

	point operator +(point q) { return point(x + q.x, y + q.y); }
	point operator -(point q) { return point(x - q.x, y - q.y); }
	point operator *(double t) { return point(x * t, y * t); }
	point operator /(double t) { return point(x / t, y / t); }
	double operator *(point q) { return x * q.x + y * q.y; }
	double operator %(point q) { return x * q.y - y * q.x; }

	int cmp(point q) const {
		if (int t = ::cmp(x, q.x)) return t;
		return ::cmp(y, q.y);
	}
	bool operator ==(point q) const { return cmp(q) == 0; }
	bool operator !=(point q) const { return cmp(q) != 0; }
	bool operator <(point q) const { return cmp(q) < 0; }
};

point origin;

int ccw(point p, point q, point r) {
	return cmp((p - r) % (q - r));
}

double angle(point p, point q, point r) {
	point u = p - q, v = r - q;
	return atan2(u % v, u * v);
}

double dist(point a, point b) {
    return hypot(a.x - b.x, a.y - b.y);
}

bool between(point p, point q, point r) {
	return ccw(p, q, r) == 0 && cmp((p - q) * (r - q)) <= 0;
}

double seg_dist(point p, point q, point r) {
    point A = r - q, B = r - p, C = q - p;
    double a = A * A, b = B * B, c = C * C;
    if (cmp(b, a + c) >= 0) return sqrt(a);
    else if (cmp(a, b + c) >= 0) return sqrt(b);
    else return fabs(A % B) / sqrt(c);
}

bool seg_intersect(point p, point q, point r, point s) {
	point A = q - p, B = s - r, C = r - p, D = s - q;
	int a = cmp(A % C) + 2 * cmp(A % D);
	int b = cmp(B % C) + 2 * cmp(B % D);
	if (a == 3 || a == -3 || b == 3 || b == -3) return false;
	if (a || b || p == r || p == s || q == r || q == s) return true;
	int t = (p < r) + (p < s) + (q < r) + (q < s);
	return t != 0 && t != 4;
}

bool parallel(point p, point q, point r, point s) {
    return fabs((q - p) % (s - r)) < EPS;
}

point line_intersect(point p, point q, point r, point s) {
	point a = q - p, b = s - r, c = point(p % q, r % s);
	return point(point(a.x, b.x) % c, point(a.y, b.y) % c) / (a % b);
}

polygon pol;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        point p = point(x, y);
        pol.push_back(p);
    }

    double ini = 0.0, fim = 10000000000.0;
    int iter = 200;
    while (iter--) {
        double mid = (ini + fim) / 2;

        bool valid = true;

        for (int i = 0; i < n; i++) {
            int nxt = (i+1) % n, sec = (i+2) % n;
            double dst = seg_dist(pol[i], pol[sec], pol[nxt]);

            if (dst < 2.0 * mid) valid = false;
        }

        if (valid) ini = mid;
        else fim = mid;
    }

    printf("%.10f\n", ini);

    return 0;
}
