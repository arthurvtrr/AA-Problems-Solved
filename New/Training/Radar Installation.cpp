#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

#define EPS 1e-9

int n, d;

struct point {
    double x;
    double y;
} points[1010];

point null = (point) {0, 0};

struct Circle {
    double x;
    double y;
    double r;

    bool contains(point p) {
        return sqrt((p.x - x)*(p.x - x) + (p.y - y)*(p.y - y)) < r + EPS;
    }
};

Circle getCircumCircle(point p1, point p2, point p3 = null) {
    Circle ret = (Circle) {0, 0, 0};

    if (p3.x == 0 && p3.y == 0) {
        ret.x = p1.x + (p2.x - p1.x) * 0.5;
        ret.y = p1.y + (p2.y - p1.y) * 0.5;
        ret.r = sqrt((p1.x - ret.x)*(p1.x - ret.x) + (p1.y - ret.y)*(p1.y - ret.y));

        return ret;
    }

    double a = p2.x - p1.x, b = p2.y - p1.y;
    double c = p3.x - p1.x, d = p3.y - p1.y;
    double e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
    double f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
    double g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
    if (fabs(g) >= EPS) {
        ret.x = (d*e - b*f) / g;
        ret.y = (a*f - c*e) / g;
        ret.r = sqrt((p1.x - ret.x)*(p1.x - ret.x) + (p1.y - ret.y)*(p1.y - ret.y));
    }

    return ret;
}

Circle minEnclosingCircle(vector < point > p) {
    if (p.size() == 0)
        return (Circle) {0, 0, 0};
    if (p.size() == 1)
        return (Circle) {p[0].x, p[0].y, 0};

    random_shuffle(p.begin(), p.end());

    Circle circle = getCircumCircle(p[0], p[1]);

    for (int i = 2; i < p.size(); i++)
        if (!circle.contains(p[i])) {
            circle = getCircumCircle(p[0], p[i]);
            for (int j = 1; j < i; j++)
                if (!circle.contains(p[j])) {
                    circle = getCircumCircle(p[j], p[i]);
                    for (int k = 0; k < j; k++)
                        if (!circle.contains(p[k]))
                            circle = getCircumCircle(p[i], p[j], p[k]);
                }
        }

    return circle;
}

bool cmp(point a, point b) {
    return a.x < b.x;
}

int main() {
    int t = 1;
    while (scanf("%d %d", &n, &d)) {
        if (n + d == 0) break;

        bool possible = true;
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &points[i].x, &points[i].y);

            if (points[i].y - EPS >= d)
                possible = false;
        }

        sort(points, points+n, cmp);

        if (!possible)
            printf("Case %d: -1\n", t++);
        else {
            int ans = 0;
            vector < point > aux;
            for (int i = 0; i < n; i++) {
                aux.push_back(points[i]);
                aux.push_back((point) {points[i].x, -points[i].y});

                if (minEnclosingCircle(aux).r - EPS >= d) {
                    ans++;
                    aux.clear();
                    i--;
                }
            }

            if (aux.size() > 0) ans++;

            printf("Case %d: %d\n", t++, ans);
        }
    }

    return 0;
}
