#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-9
int t, a, b, c;

struct point {
    double x, y, z;
    point() { x = y = z = 0.0; }
    point(double x, double y, double z) : x(x), y(y), z(z) {}
} shipa[4], shipb[4];

double dist(point a, point b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

struct vec {
    double x, y, z;
    vec(double x, double y, double z) : x(x), y(y), z(z) {}
};

vec toVec(point a, point b) {
    return vec(b.x - a.x, b.y - a.y, b.z - a.z);
}

vec scale(vec v, double s) {
    return vec(v.x * s, v.y * s, v.z * s);
}

point translate(point p, vec v) {
    return point(p.x + v.x, p.y + v.y, p.z + v.z);
}

vec add(vec p, vec v) {
    return vec(p.x + v.x, p.y + v.y, p.z + v.z);
}

double dot(vec a, vec b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y + v.z * v.z; }

double distToLine(point p, point a, point b) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    point c = translate(a, scale(ab, u));
    return dist(p, c);
}

double distToLineS(point p, point a, point b) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) return dist(p, a);
    if (u > 1.0) return dist(p, b);
    return distToLine(p, a, b);
}

vec norm(vec a, vec b) {
    return vec(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

double area(point a, point b, point c) {
    return sqrt(norm_sq(norm(toVec(a, b), toVec(a, c)))) / 2.0;
}

double inside(point p, point a, point b, point c) {
    vec ab = toVec(a, b), ac = toVec(a, c);
    vec n = norm(ab, ac);
    n = scale(n, 1.0 / sqrt(norm_sq(n)));

    double d = -a.x*n.x - a.y*n.y - a.z*n.z;
    double dst = dot(n, vec(p.x, p.y, p.z)) + d;

    point pj = translate(p, scale(n, -dot(toVec(a, p), n)));

    double area1 = area(a, b, c), area2 = 0.0;
    area2 += area(a, b, pj);
    area2 += area(b, c, pj);
    area2 += area(c, a, pj);

    if (fabs(area1 - area2) < EPS) return fabs(dst);
    return -1.0;
}

double distseg(point p1, point p2, point p3, point p4) {
    vec u = toVec(p1, p2);
    vec v = toVec(p3, p4);
    vec w = toVec(p3, p1);
    double a = dot(u, u);
    double b = dot(u, v);
    double c = dot(v, v);
    double d = dot(u, w);
    double e = dot(v, w);
    double D = a*c - b*b;
    double sc, sN, sD = D;
    double tc, tN, tD = D;

    if (D < EPS) {
        sN = 0.0; sD = 1.0; tN = e; tD = c;
    }
    else {
        sN = (b*e - c*d);
        tN = (a*e - b*d);
        if (sN < 0.0) {
            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if (sN > sD) {
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }

    if (tN < 0.0) {
        tN = 0.0;
        if (-d < 0.0) sN = 0.0;
        else if (-d > a) sN = sD;
        else {
            sN = -d;
            sD = a;
        }
    }
    else if (tN > tD) {
        tN = tD;
        if ((-d + b) < 0.0) sN = 0;
        else if ((-d + b) > a) sN = sD;
        else {
            sN = (-d +  b);
            sD = a;
        }
    }

    sc = (abs(sN) < EPS ? 0.0 : sN / sD);
    tc = (abs(tN) < EPS ? 0.0 : tN / tD);

    vec dP = add(w, scale(u, sc));
    dP = add(dP, scale(v, -tc));

    return sqrt(norm_sq(dP));
}

int main() {
    scanf("%d", &t);

    while (t--) {
        for (int i = 0; i < 4; i++) {
            scanf("%d %d %d", &a, &b, &c);
            shipa[i] = point(a, b, c);
        }
        for (int i = 0; i < 4; i++) {
            scanf("%d %d %d", &a, &b, &c);
            shipb[i] = point(a, b, c);
        }

        double ans = DBL_MAX;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                for (int k = j+1; k < 4; k++)
                    ans = min(ans, distToLineS(shipa[i], shipb[j], shipb[k]));

            for (int j = 0; j < 4; j++)
                for (int k = j+1; k < 4; k++)
                    for (int l = k+1; l < 4; l++) {
                        double d = inside(shipa[i], shipb[j], shipb[k], shipb[l]);
                        if (d > 0.0) ans = min(ans, d);
                    }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                for (int k = j+1; k < 4; k++)
                    ans = min(ans, distToLineS(shipb[i], shipa[j], shipa[k]));

            for (int j = 0; j < 4; j++)
                for (int k = j+1; k < 4; k++)
                    for (int l = k+1; l < 4; l++) {
                        double d = inside(shipb[i], shipa[j], shipa[k], shipa[l]);
                        if (d > 0.0) ans = min(ans, d);
                    }
        }

        for (int i = 0; i < 4; i++)
            for (int j = i+1; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    for (int l = k+1; l < 4; l++)
                        ans = min(ans, distseg(shipa[i], shipa[j], shipb[k], shipb[l]));

        printf("%.2f\n", ans);
    }

    return 0;
}
