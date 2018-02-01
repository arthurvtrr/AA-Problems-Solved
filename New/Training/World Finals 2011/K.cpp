#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-9

int n, x, y;

struct point {
    double x, y;
    point() { x = y = 0; }
    point(double x, double y) : x(x), y(y) {}
    bool operator < (point other) const {
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        return y < other.y;
    }
};

struct vec {
    double x, y;
    vec(double x, double y) : x(x), y(y) {}
};

vec toVec(point a, point b) {
    return vec(b.x - a.x, b.y - a.y);
}

vec scale(vec v, double s) {
    return vec(v.x * s, v.y * s);
}

point translate(point p, vec v) {
    return point(p.x + v.x, p.y + v.y);
}

double dot(vec a, vec b) { return a.x * b.x + a.y * b.y; }
double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }
double dist(point a, point b) { return hypot(a.x - b.x, a.y - b.y); }

double distToLine(point p, point a, point b) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    point c = translate(a, scale(ab, u));
    return dist(p, c);
}

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

double ccw(point p, point q, point r) {
    return cross(toVec(r, p), toVec(r, q));
}

vector < point > pol, conv;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

point pivot;

bool radial_lt(point p, point q) {
    vec P = toVec(pivot, p), Q = toVec(pivot, q);
    double R = cross(P, Q);
    if (cmp(R)) return R > 0;
    return cmp(dot(P, P), dot(Q, Q)) < 0;
}

vector < point > convex_hull(vector < point >& T) {
    int j = 0, k, n = T.size(); vector < point > U(n);

    pivot = *min_element(T.begin(), T.end());
    sort(T.begin(), T.end(), radial_lt);

    for (k = n-2; k >= 0 && ccw(T[0], T[n-1], T[k]) == 0; k--);
    reverse((k+1) + T.begin(), T.end());

    for (int i = 0; i < n; i++) {
        while (j > 1 && ccw(U[j-1], U[j-2], T[i]) >= 0) j--;
        U[j++] = T[i];
    }

    U.erase(j + U.begin(), U.end());
    return U;
}

int main() {
    int t = 1;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        pol.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            point p = point(x, y);
            pol.push_back(p);
        }

        conv = convex_hull(pol);

        int siz = conv.size();

        double ans = DBL_MAX;
        for (int i = 0; i < siz; i++) {
            double aux = 0.0;
            for (int j = 0; j < siz; j++)
                aux = max(aux, distToLine(conv[j], conv[i], conv[(i+1)%siz]));
            ans = min(ans, aux);
        }

        printf("Case %d: %.2f\n", t++, ans);
    }
    return 0;
}

