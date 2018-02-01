#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

#define EPS 1e-9
#define PI acos(-1)

int n;

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

int main() {
    string line;

	while(getline(cin, line)) {
        polygon.clear();
        convHull.clear();

        double x = 0, y = 0;
        bool second = false, neg_x = false, neg_y = false, frac = false;
        int pos = 0;

		for (int i = 0; i < line.size(); i++) {
            if (line[i] == '-') {
                if (!second) neg_x = true;
                else neg_y = true;
            }
            else if (line[i] >= '0' && line[i] <= '9') {
                if (!second && !frac) {
                    x *= 10;
                    x += line[i] - '0';
                }
                else if (second && !frac) {
                    y *= 10;
                    y += line[i] - '0';
                }
                else if (!second && frac) {
                    pos++;
                    double div = 1;
                    for (int j = 0; j < pos; j++)
                        div *= 10;

                    x += (line[i] - '0') * 1.0 / div;
                }
                else {
                    pos++;
                    double div = 1;
                    for (int j = 0; j < pos; j++)
                        div *= 10;

                    y += (line[i] - '0') * 1.0 / div;
                }
            }
            else if (line[i] == ',') {
                second = true;
                frac = false;
            }
            else if (line[i] == '.') {
                frac = true;
                pos = 0;
            }
			else if (line[i] == ')') {
                polygon.push_back(point((neg_x? -1 : 1)*x, (neg_y? -1 : 1)*y));
                x = y = second = neg_x = neg_y = frac = 0;
            }
		}

		convexHull(polygon, convHull);
		convHull.push_back(convHull[0]);

		int siz = convHull.size();

		for (int i = 0; i < siz; i++) {
			if (i > 0) printf(" ");
            printf("(%f,%f)", convHull[i].x, convHull[i].y);
		}
		printf("\n");
	}
	return 0;
}
