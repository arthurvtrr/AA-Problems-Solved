#include <bits/stdc++.h>

using namespace std;

#define PI acos(-1)
#define EPS 1e-9

int t, n, m, a, b, c, d;

int cmp(long double x, long double y = 0, long double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point {
    long double x, y;
    int t, ind;
    point(long double x = 0, long double y = 0, int t = 0, int ind = 0) : x(x), y(y), t(t), ind(ind) {}

    point operator -(point q) { return point(x - q.x, y - q.y); }
    long double operator *(point q) { return x * q.x + y * q.y; }
    long double operator %(point q) { return x * q.y - y * q.x; }

    int cmp(point q) const {
        if (int t = ::cmp(x, q.x)) return t;
        return ::cmp(y, q.y);
    }
} points[2020];

long double angle(point p, point q, point r) {
    point u = p - q, v = r - q;
    return atan2(u % v, u * v);
}

struct e {
    long double ang;
    int t, c;
    e(long double ang = 0, int t = 0, int c = 0) : ang(ang), t(t), c(c) {}
};

vector < e > ev;

bool cmp1(e a, e b) {
    return a.ang < b.ang;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &a, &b);
            points[i] = point(a, b, 0, i);
        }
        for (int i = n; i < n+m; i++) {
            scanf("%d %d", &a, &b);
            points[i] = point(a, b, 1, i);
        }

        int ans = INT_MAX;

        for (int i = 0; i < n+m; i++) {
            int esq[2] = {0, 0}, dir[2] = {0, 0};
            ev.clear();
            for (int j = 0; j < n+m; j++) {
                if (i == j) continue;
                long double ang = angle(points[j], points[i], point(points[i].x + 10.0, points[i].y));
                ang *= 180.0 / PI;
                if (ang < 0.0) ang += 360.0;

                if (ang >= 180.0) dir[points[j].t]++;

                ev.push_back(e(ang, 0, points[j].t));
                ev.push_back(e(ang >= 180.0? ang - 180.0 : ang + 180.0, 1, points[j].t));
            }
            sort(ev.begin(), ev.end(), cmp1);

            esq[0] = n - dir[0] - (points[i].t == 0);
            esq[1] = m - dir[1] - (points[i].t == 1);

            //printf("\n");
            //printf("%d %d %d %d\n", esq[0], esq[1], dir[0], dir[1]);

            ans = min(ans, esq[0] + dir[1]);
            ans = min(ans, esq[1] + dir[0]);

            for (int j = 0; j < ev.size(); j++) {
                if (ev[j].t == 0) {
                    dir[ev[j].c]++;
                    esq[ev[j].c]--;
                }
                else {
                    esq[ev[j].c]++;
                    dir[ev[j].c]--;
                }

                //printf("%d %d %d %d\n", esq[0], esq[1], dir[0], dir[1]);
                ans = min(ans, esq[0] + dir[1]);
                ans = min(ans, esq[1] + dir[0]);
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
