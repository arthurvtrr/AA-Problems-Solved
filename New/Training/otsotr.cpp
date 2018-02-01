#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <map>
#include <set>

using namespace std;

#define EPS 1e-10

struct point {
    double x, y;
    point() { x = y = 0; }
    point(double x, double y) : x(x), y(y) {}

    bool operator < (point other) const {
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        if (fabs(y - other.y) > EPS)
            return y < other.y;
        return false;
    }
};

struct line { double a, b, c; };

void pointsToLine(point p1, point p2, line &l) {
    if (fabs(p1.x - p2.x) < EPS) {
        l.a = 1.0; l.b = 0.0; l.c = -p1.x;
    } else {
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;
        l.c = -(double)(l.a * p1.x) - p1.y;
    }
}

bool areParallel(line l1, line l2) {
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(line l1, line l2) {
    return areParallel(l1, l2) && (fabs(l1.c-l2.c) < EPS);
}

bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false;

    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);

    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else p.y = -(l2.a * p.x + l2.c);
    return true;
}

int n;
point points[1010];
map < point, set < int > > notVis;
set < int > ways;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf %lf", &points[i].x, &points[i].y);

    line axis;
    pointsToLine(point(0, 0), point(10, 0), axis);

    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            line aux;
            pointsToLine(points[i], points[j], aux);
            point p;

            if (areIntersect(axis, aux, p)) {
                if (points[i].y < points[j].y + EPS) notVis[p].insert(j);
                else notVis[p].insert(i);
            }
        }

    ways.insert(n);
    for (map < point, set < int > >::iterator it = notVis.begin(); it != notVis.end(); it++)
        ways.insert(n - (it->second).size());

    printf("%d\n", ways.size());
    return 0;
}
