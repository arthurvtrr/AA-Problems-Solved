#include <stdio.h>
#include <algorithm>

using namespace std;

#define EPS 1e-9
#define PI acos(-1)

int n;

struct point {
	int x;
	int y;
	double ang;

	point(int x = 0, int y = 0): x(x), y(y) {}

	point operator +(point q) { return point(x + q.x, y + q.y); }
	point operator -(point q) { return point(x - q.x, y - q.y); }
	double operator *(point q) { return x * q.x + y * q.y; }
	double operator %(point q) { return x * q.y - y * q.x; }

} points[110000];

double angle(point p, point q, point r) {
	point u = p - q, v = r - q;
	return atan2(u % v, u * v);
}

bool cmp(point a, point b) {
	return a.ang < b.ang;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &points[i].x, &points[i].y);
		points[i].ang = angle(point(10000, 0), point(), points[i]) * 180.0 / PI;
		if (points[i].ang < EPS)
			points[i].ang = 360.0 + points[i].ang;
	}

	sort(points, points+n, cmp);

	double sol = 360.0;

	for (int i = 0; i < n; i++) {
		double ang = angle(points[i], point(), points[(i + n - 1) % n]) * 180.0 / PI;
		if (ang < EPS)
			ang = 360.0 + ang;

		if (sol > ang - EPS)
			sol  = ang;
	}

	if (fabs(360.0 - sol) < EPS) sol = 0.0;

	printf("%.10f\n", sol);
	return 0;
}
