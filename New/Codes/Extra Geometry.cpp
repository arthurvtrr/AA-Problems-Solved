#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI acos(-1)

// convert point and gradient/slope to line
void pointSlopeToLine(point p, double m, line &l) {
  l.a = -m;
  l.b = 1;
  l.c = -((l.a * p.x) + (l.b * p.y));
}

// returns 1 if there is a circumCenter center, returns 0 otherwise
// if this function returns 1, ctr will be the circumCircle center
// and r is the same as rCircumCircle
int circumCircle(point p1, point p2, point p3, point &ctr, double &r){
  double a = p2.x - p1.x, b = p2.y - p1.y;
  double c = p3.x - p1.x, d = p3.y - p1.y;
  double e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
  double f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
  double g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
  if (fabs(g) < EPS) return 0;

  ctr.x = (d*e - b*f) / g;
  ctr.y = (a*f - c*e) / g;
  r = dist(p1, ctr);  // r = distance from center to 1 of the 3 points
  return 1;
}

// returns true if point d is inside the circumCircle defined by a,b,c
int inCircumCircle(point a, point b, point c, point d) {
  return (a.x - d.x) * (b.y - d.y) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) +
         (a.y - d.y) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.x - d.x) +
         ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.x - d.x) * (c.y - d.y) -
         ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.y - d.y) * (c.x - d.x) -
         (a.y - d.y) * (b.x - d.x) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) -
         (a.x - d.x) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.y - d.y) > 0 ? 1 : 0;
}

//Check if point is inside of a convex polygon in O(log(n))
bool inConvexPoly(const vector < int > &convPoly, point p) {
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
