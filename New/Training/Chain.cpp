#include <bits/stdc++.h>

using namespace std;

int t, n;

struct link {
    int coord[2][3];
} links[1000100];

#define EPS 1e-8

int cmp(double x, double y = 0) {
	return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
}

struct point {
	double x, y;
	point(double x = 0, double y = 0): x(x), y(y) {}

	point operator +(point q) { return point(x + q.x, y + q.y); }
	point operator -(point q) { return point(x - q.x, y - q.y); }
	point operator *(double t) { return point(x * t, y * t); }
	point operator /(double t) { return point(x / t, y / t); }
	double operator *(point q) { return x * q.x + y * q.y; }
	double operator %(point q) { return x * q.y - y * q.x; }

	int cmp(point q) const {
		if (int t = ::cmp(x, q.x)) return t;
		return ::cmp(y, q.y);
	}
	bool operator ==(point q) const { return cmp(q) == 0; }
	bool operator !=(point q) const { return cmp(q) != 0; }
	bool operator <(point q) const { return cmp(q) < 0; }
};

#define polygon vector < point >

point origin;

int ccw(point p, point q, point r) {
	return cmp((p - r) % (q - r));
}

bool polCmp(point p, point q) {
    point P = p - origin, Q = q - origin;
    double R = P % Q;
    if (cmp(R)) return R > 0;
    return cmp(P * P, Q * Q) < 0;
}

double angle(point p, point q, point r) {
	point u = p - q, v = r - q;
	return atan2(u % v, u * v);
}

bool between(point p, point q, point r) {
	return ccw(p, q, r) == 0 && cmp((p - q) * (r - q)) <= 0;
}

bool seg_intersect(point p, point q, point r, point s) {
	point A = q - p, B = s - r, C = r - p, D = s - q;
	int a = cmp(A % C) + 2 * cmp(A % D);
	int b = cmp(B % C) + 2 * cmp(B % D);
	if (a == 3 || a == -3 || b == 3 || b == -3) return false;
	if (a || b || p == r || p == s || q == r || q == s) return true;
	int t = (p < r) + (p < s) + (q < r) + (q < s);
	return t != 0 && t != 4;
}

point line_intersect(point p, point q, point r, point s) {
	point a = q - p, b = s - r, c = point(p % q, r % s);
	return point(point(a.x, b.x) % c, point(a.y, b.y) % c) / (a % b);
}

int in_poly(point p, polygon& T) {
	double a = 0; int N = T.size();
	for (int i = 0; i < N; i++) {
		if (between(T[i], p, T[(i+1) % N])) return -1;
		a += angle(T[i], p, T[(i+1) % N]);
	}
	return cmp(a) != 0;
}

polygon poly_intersect(polygon& P, polygon& Q) {
	int m = Q.size(), n = P.size();
	int a = 0, b = 0, aa = 0, ba = 0, inflag = 0;
	polygon R;

	while ((aa < n || ba < m) && aa < 2*n && ba < 2*m) {
		point p1 = P[a], p2 = P[(a+1) % n], q1 = Q[b], q2 = Q[(b+1) % m];
		point A = p2 - p1, B = q2 - q1;
		int cross = cmp(A % B), ha = ccw(p2, q2, p1), hb = ccw(q2, p2, q1);
		if (cross == 0 && ccw(p1, q1, p2) == 0 && cmp(A * B) < 0) {
			if (between(p1, q1, p2)) R.push_back(q1);
			if (between(p1, q2, p2)) R.push_back(q2);
			if (between(q1, p1, q2)) R.push_back(p1);
			if (between(q1, p2, q2)) R.push_back(p2);
			if (R.size() < 2) return polygon();
			inflag = 1; break;
		}
		else if (cross != 0 && seg_intersect(p1, p2, q1, q2)) {
			if (inflag == 0) aa = ba = 0;
			R.push_back(line_intersect(p1, p2, q1, q2));
			inflag = (hb > 0)? 1 : -1;
		}

		if (cross == 0 && hb < 0 && ha < 0) return R;
		bool t = cross == 0 && hb == 0 && ha == 0;
		if (t ? (inflag == 1) : (cross >= 0) ? (ha <= 0) : (hb > 0)) {
			if (inflag == -1) R.push_back(q2);
			ba++; b++; b %= m;
		}
		else {
			if (inflag == 1) R.push_back(p2);
			aa++; a++; a %= n;
		}
	}
	if (inflag == 0) {
		if (in_poly(P[0], Q)) return P;
		if (in_poly(Q[0], P)) return Q;
	}
	R.erase(unique(R.begin(), R.end()), R.end());
	if (R.size() > 1 && R.front() == R.back()) R.pop_back();
	return R;
}

polygon get_rectangle(point a, point b) {
    polygon ret;
    ret.push_back(a); ret.push_back(b);
    ret.push_back(line_intersect(a, point(a.x, a.y + 1.0), b, point(b.x + 1.0, b.y)));
    ret.push_back(line_intersect(a, point(a.x + 1.0, a.y), b, point(b.x, b.y + 1.0)));
    sort(ret.begin(), ret.end());
    origin = ret[0];
    sort(ret.begin(), ret.end(), polCmp);
    return ret;
}

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &links[i].coord[0][0], &links[i].coord[0][1], &links[i].coord[0][2]);
            scanf("%d %d %d", &links[i].coord[1][0], &links[i].coord[1][1], &links[i].coord[1][2]);
        }

        bool valid = false;

        for (int axis = 0; axis < 3; axis++) {
            vector < polygon > setA;
            int minv = 1000000000, maxv = -1000000000;

            vector < int > d;
                for (int j = 0; j < 3; j++)
                    if (j != axis) d.push_back(j);

            for (int i = 0; i < n; i++)
                if (links[i].coord[0][axis] == links[i].coord[1][axis]) {
                    minv = min(minv, links[i].coord[0][axis]);
                    maxv = max(maxv, links[i].coord[0][axis]);

                    point a = point(links[i].coord[0][d[0]], links[i].coord[0][d[1]]);
                    point b = point(links[i].coord[1][d[0]], links[i].coord[1][d[1]]);
                    polygon aux = get_rectangle(a, b);

                    setA.push_back(aux);
                }

            if (setA.size() == 0 || setA.size() == n) continue;

            polygon intersection = setA[0];
            for (int i = 1; i < setA.size(); i++) {
                intersection = poly_intersect(intersection, setA[i]);
                if (intersection.size() != 4) break;
            }

            if (intersection.size() != 4) continue;

            bool possible = true;
            for (int i = 0; i < n; i++) {
                int eq;
                for (int j = 0; j < 3; j++)
                    if (links[i].coord[0][j] == links[i].coord[1][j])
                        eq = j;

                if (eq != axis) {
                    point a = point(links[i].coord[0][d[0]], links[i].coord[0][d[1]]);
                    point b = point(links[i].coord[1][d[0]], links[i].coord[1][d[1]]);

                    int mini = links[i].coord[0][axis], maxi = links[i].coord[1][axis];
                    if (mini > maxi) swap(mini, maxi);

                    int x = in_poly(a, intersection), y = in_poly(b, intersection);

                    if (mini < minv && maxi > maxv && x != y) continue;
                    else possible = false;
                }
            }

            if (possible) valid = true;
        }

        if (valid) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
