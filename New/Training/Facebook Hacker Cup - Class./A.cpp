#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

#define EPS 1e-9
#define PI acos(-1)

int t, p, x, y;

struct point {
    double x, y;
    point() { x = y = 0; }
    point(double _x, double _y) : x(_x), y(_y) {}
};

double dist(point p1, point p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

struct vec {
    double x, y;
    vec() { x = y = 0; }
    vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(point a, point b) {
    return vec(b.x - a.x, b.y - a.y);
}

double dot(vec a, vec b) {
    return a.x * b.x + a.y * b.y;
}

double norm_sq(vec v) {
    return v.x * v.x + v.y * v.y;
}

double angle(point a, point o, point b) {
    vec oa = toVec(o, a), ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d %d %d", &p, &x, &y);

        if (p == 0) {
            printf("Case #%d: white\n", tc+1);
            continue;
        }
        if (x == 50 && y == 50) {
            printf("Case #%d: black\n", tc+1);
            continue;
        }

        bool black = false;
        if (dist(point(50, 50), point(x, y)) < 50.0 + EPS) {
            double ang = angle(point(50, 100), point(50, 50), point(x, y)) * 180.0 / PI;
            if (x < 50.0) ang = 360.0 - ang;

            if (ang < p / 100.0 * 360.0 + EPS) black = true;
        }

        if (black) printf("Case #%d: black\n", tc+1);
        else printf("Case #%d: white\n", tc+1);
    }

    return 0;
}
