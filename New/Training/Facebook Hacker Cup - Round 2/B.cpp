#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <stack>
#include <vector>

using namespace std;

#define EPS 1e-9
#define pii pair < long long, long long >

int t, n;
long long ax, bx, cx, ah, bh, ch;

struct point {
    double x, y;
    point() { x = y = 0; }
    point(double _x, double _y) : x(_x), y(_y) {}
};

struct pole {
    long long x, h;
} poles[800800];

bool cmp(pole a, pole b) {
    return a.x < b.x;
}

bool cmp1(point a, point b) {
    return a.x < b.x;
}

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
    return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false;
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);

    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else p.y = -(l2.a * p.x + l2.c);

    return true;
}

point center = point();

bool cmp2(point a, point b) {
    return atan2(a.y - center.y, a.x - center.x) < atan2(b.y - center.y, b.x - center.x);
}

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d", &n);
        scanf("%lld %lld %lld %lld", &poles[1].x, &ax, &bx, &cx);
        scanf("%lld %lld %lld %lld", &poles[1].h, &ah, &bh, &ch);

        for (int i = 2; i <= n; i++) {
            poles[i].x = ((ax * poles[i-1].x + bx) % cx) + 1;
            poles[i].h = ((ah * poles[i-1].h + bh) % ch) + 1;
        }

        for (int i = 1; i <= n; i++)
            printf("%lld\n", poles[i].x);
        sort(poles+1, poles+n+1, cmp);

        stack < pii > aux;
        aux.push(make_pair(poles[1].x, poles[1].h));

        for (int i = 2; i <= n; i++)
            while (!aux.empty()) {
                long long a = aux.top().first, b = aux.top().second;

                if (poles[i].h < b && abs(poles[i].h - b) > abs(poles[i].x - a)) break;
                else if (b < poles[i].h && abs(poles[i].h - b) > abs(poles[i].x - a)) aux.pop();
                else {
                    aux.push(make_pair(poles[i].x, poles[i].h));
                    break;
                }
            }

        vector < point > points;

        while (!aux.empty()) {
            points.push_back(point(aux.top().first, aux.top().second));
            aux.pop();
        }

        sort(points.begin(), points.end(), cmp1);

        int siz = points.size();
        points.push_back(point(points[siz-1].x+points[siz-1].y, 0));
        points.push_back(point(points[0].x-points[0].y, 0));

        for (int i = 0; i < siz-1; i++) {
            line a, b;
            pointsToLine(points[i], point(points[i].x+points[i].y, 0), a);
            pointsToLine(points[i+1], point(points[i+1].x-points[i+1].y, 0), b);
            point p;
            if (areIntersect(a, b, p) && p.y > -EPS)
                points.push_back(p);
        }

        sort(points.begin(), points.end(), cmp1);
        sort(points.begin()+1, points.end(), cmp2);
        points.push_back(points[0]);

        for (int i = 0; i < (int)points.size(); i++)
            printf("%f %f\n", points[i].x, points[i].y);

        double sol = 0.0;
        for (int i = 0; i < (int)points.size()-1; i++) {
            sol += (points[i].x * points[i+1].y - points[i+1].x * points[i].y);
        }
        sol = fabs(sol) / 2.0;
        printf("Case #%d: %f\n", tc+1, sol);
    }
    return 0;
}

