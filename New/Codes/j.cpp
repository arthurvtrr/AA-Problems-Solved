#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

#define EPS 1e-12
#define PI acos(-1)

struct point {
    long double x, y;
    point() { x = y = 0.0;}
    point (long double x, long double y) : x(x), y(y) {}
    point(const point &p) : x(p.x), y(p.y) {}
    point operator + (const point &p) const { return point(x+p.x, y+p.y); }
    point operator - (const point &p) const { return point(x-p.x, y-p.y); }
    point operator * (long double c) const { return point(x*c, y*c); }
    point operator / (long double c) const { return point(x/c, y/c); }
    double operator *(point q) { return x * q.x + y * q.y; }
    double operator %(point q) { return x * q.y - y * q.x; }
};

long double dist(point a, point b) {
    return hypot(a.x - b.x, a.y - b.y);
}
point RotateCCW90(point p) { return point(-p.y, p.x); }

vector < point > CircleCircleIntersection(point a, point b, long double r, long double R) {
    vector < point > ret;
    long double d = dist(a, b);
    if (d > r+R || d+min(r, R) < max(r, R)) return ret;
    long double x = (d*d-R*R+r*r)/(2*d);
    long double y = sqrt(r*r-x*x);
    point v = (b-a)/d;
    ret.push_back(a+v*x + RotateCCW90(v)*y);
    if (y > 0) ret.push_back(a+v*x - RotateCCW90(v)*y);
    return ret;
}

struct vec {
    long double x, y;
    vec(long double _x, long double _y) : x(_x), y(_y) {}
};

vec toVec(point a, point b) {
    return vec(b.x - a.x, b.y - a.y);
}

vec scale(vec v, long double s) {
    return vec(v.x * s, v.y * s);
}

point translate(point p, vec v) {
    return point(p.x + v.x, p.y + v.y);
}

long double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }
long double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

long double angle(point a, point o, point b) {
    point u = a - o, v = b - o;
    long double x = atan2(u % v, u * v);
    return x;
}

long double area(long double a, long double b, long double c) {
    long double s = (a + b + c) / 2.0;
    long double area = sqrt(s) * sqrt(s - a) * sqrt(s - b) * sqrt(s - c);
    return area;
}

struct line { long double a, b, c; };

long double distProjec(point p, point a, point b, point x) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    long double u = dot(ap, ab) / norm_sq(ab);
    point c = translate(a, scale(ab, u));
    return dist(c, x);
}

int main() {
    long double x1_, y1_, r1_, x2_, y2_, r2_;
    cin >> x1_ >> y1_ >> r1_ >> x2_ >> y2_ >> r2_;

    long double r_maior, r_menor, dist_r = dist(point(x1_, y1_), point(x2_, y2_));
    point p_maior, p_menor;

    if (r1_ < r2_ - EPS) {
        r_menor = r1_;
        r_maior = r2_;
        p_menor = point(x1_, y1_);
        p_maior = point(x2_, y2_);
    }
    else {
        r_menor = r2_;
        r_maior = r1_;
        p_menor = point(x2_, y2_);
        p_maior = point(x1_, y1_);
    }

    if (x1_ == x2_ && y1_ == y2_ && r1_ == r2_) {
        cout << fixed;
        cout << setprecision(12) << r1_*r1_*PI;
        //printf("%.7Lf\n", r1_*r1_*PI);
    }
    else if (r_maior + r_menor < dist_r + EPS) {
        printf("%.7f\n", 0.0);
    }
    else if (dist_r  + r_menor < r_maior + EPS) {
        cout << fixed;
        cout << setprecision(12) << fmin(r1_ * r1_ * PI, r2_ * r2_ * PI);
        //printf("%.7Lf\n", fmin(r1_ * r1_ * PI, r2_ * r2_ * PI));
    }
    else {
        vector < point > intersec = CircleCircleIntersection(p_menor, p_maior, r_menor, r_maior);
        //printf("%f %f ; %f %f\n", intersec[0].x, intersec[0].y, intersec[1].x, intersec[1].y);
        //printf("%f\n", r_menor * r_menor * PI);

        if (intersec.size() < 2) printf("%.7f\n", 0.0);
        else {
            long double ang1 = angle(intersec[0], p_menor, intersec[1]) * 180.0 / PI;
            if (ang1 < EPS)
                ang1 = 360.0 + ang1;
            ang1 = 0.0;

            long double ang2 = angle(intersec[0], p_maior, intersec[1]) * 180.0 / PI;
            if (ang2 < EPS)
                ang2 = 360.0 + ang2;

            long double sec1 = ang1 / 360.0 * (r_menor * r_menor * PI);
            long double seg1 = sec1 - area(r_menor, r_menor, dist(intersec[0], intersec[1]));
            long double sec2 = ang2 / 360.0 * (r_maior * r_maior * PI);
            long double seg2 = sec2 - area(r_maior, r_maior, dist(intersec[0], intersec[1]));

            long double sol;

            cout << ang1 << " " << ang2 << endl;

            if (dist_r < distProjec(intersec[0], p_maior, p_menor, p_maior) - EPS)
                sol = fmin(r1_ * r1_ * PI, r2_ * r2_ * PI) - seg1 + seg2;
            else
                sol = seg1 + seg2;

            cout << fixed;
            cout << setprecision(12) << sol;
            //printf("%.7Lf\n", sol);
        }
    }
    return 0;
}

/*HPC PJVYMIY
BLMRGJIAS
*/
////
