#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

#define EPS 1e-9
#define PI acos(-1)

int n;
double x, y, w, h, ang;

//Points
struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}

	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS)
			return x < other.x;
		return y < other.y;
	}
};

double dist(point p1, point p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

point rotate(point p, double theta, point c) {
    double rad = theta * PI / 180.0;
    p.x -= c.x;
    p.y -= c.y;

    return point(p.x * cos(rad) - p.y * sin(rad) + c.x,
                 p.x * sin(rad) + p.y * cos(rad) + c.y);
}

//Polygons
vector < point > polygon, convHull;

double cross(point a, point b) {
	return a.x * b.y - a.y * b.x;
}
double cross(point O, point a, point b) {
	return cross(point(a.x - O.x, a.y - O.y), point(b.x - O.x, b.y - O.y));
}

template < int M > void findPoints(vector < point >& points, vector < point >& res) {
	for (int i = 0; i < points.size(); i++) {
		point& p = points[i];
		while (res.size() >= 2 && M * cross(res.end()[-2], res.end()[-1], p) >= 0)
			res.pop_back();
		res.push_back(p);
	}
}

void convexHull(vector < point >& points, vector < point >& result) {
	vector < point > lowerResult;
	sort(points.begin(), points.end());
	findPoints<1>(points, result);
	findPoints<-1>(points, lowerResult);
	for (int i = lowerResult.size()-2; i; i--)
		result.push_back(lowerResult[i]);
}

double area(vector < point >& p) {
    double result = 0.0;
    for (int i = 0; i < (int) p.size()-1; i++)
        result += p[i].x * p[i+1].y - p[i+1].x * p[i].y;
    return fabs(result) / 2.0;
}

int main() {
	int t;
	scanf("%d", &t);

	for (int tc = 0; tc < t; tc++) {
        polygon.clear();
        convHull.clear();

        scanf("%d", &n);

        double boards_area = 0.0;

		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf %lf", &x, &y, &w, &h, &ang);
			boards_area += w * h;

			double dif_w = w / 2.0, dif_h = h / 2.0;

			point a = point(x - dif_w, y - dif_h);
			point b = point(x - dif_w, y + dif_h);
			point c = point(x + dif_w, y - dif_h);
			point d = point(x + dif_w, y + dif_h);

			point center = point(x, y);

            double to_rotate = -ang;

			polygon.push_back(rotate(a, to_rotate, center));
			polygon.push_back(rotate(b, to_rotate, center));
			polygon.push_back(rotate(c, to_rotate, center));
			polygon.push_back(rotate(d, to_rotate, center));
		}

		convexHull(polygon, convHull);
		reverse(convHull.begin()+1, convHull.end());
		convHull.push_back(convHull[0]);

		double convexArea = area(convHull);
		boards_area *= 100.0;

		printf("%.1f %%\n", boards_area / convexArea);
	}
	return 0;
}

