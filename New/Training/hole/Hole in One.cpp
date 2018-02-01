#include <bits/stdc++.h>

using namespace std;

#define polygon vector < point >
#define wall pair < point, point >
#define interval pair < double, double >
#define EPS 1e-9
#define PI acos(-1)

int n, x_1, y_1, x_2, y_2;

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

point hole, xhole, origin;
wall walls[10];

int ccw(point p, point q, point r) {
	return cmp((p - r) % (q - r));
}

double angle(point p, point q, point r) {
	point u = p - q, v = r - q;
	return atan2(u % v, u * v);
}

double dist(point a, point b) {
    return hypot(a.x - b.x, a.y - b.y);
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

bool parallel(point p, point q, point r, point s) {
    return fabs((q - p) % (s - r)) < EPS;
}

point line_intersect(point p, point q, point r, point s) {
	point a = q - p, b = s - r, c = point(p % q, r % s);
	return point(point(a.x, b.x) % c, point(a.y, b.y) % c) / (a % b);
}

void invert_walls(vector < wall >& aux, int pos) {
    if (fabs(aux[pos].first.x - aux[pos].second.x) < EPS) {
        for (int i = 0; i < n; i++)
            if (i != pos) {
                aux[i].first.x += 2 * (aux[pos].first.x - aux[i].first.x);
                aux[i].second.x += 2 * (aux[pos].second.x - aux[i].second.x);
            }
    }
    else {
        for (int i = 0; i < n; i++)
            if (i != pos) {
                aux[i].first.y += 2 * (aux[pos].first.y - aux[i].first.y);
                aux[i].second.y += 2 * (aux[pos].second.y - aux[i].second.y);
            }
    }
}

bool valid(vector < int >& ind) {
    vector < wall > aux;
    for (int j = 0; j < n; j++)
        aux.push_back(walls[j]);

    xhole = hole;
    origin = point(0, 0);

    for (int j = 0; j < ind.size(); j++) {
        invert_walls(aux, ind[j]);
        if (fabs(aux[ind[j]].first.x - aux[ind[j]].second.x) < EPS)
            xhole.x += 2 * (aux[ind[j]].first.x - xhole.x);
        else
            xhole.y += 2 * (aux[ind[j]].first.y - xhole.y);
    }

    aux.clear();
    for (int j = 0; j < n; j++)
        aux.push_back(walls[j]);

    for (int i = 0; i < ind.size(); i++) {
        wall left = aux[ind[i]];
        if (parallel(origin, xhole, left.first, left.second))
            return false;

        point p = line_intersect(origin, xhole, left.first, left.second);

        if (seg_intersect(origin, xhole, left.first, left.second)) {
            for (int j = 0; j < n; j++) {
                bool valid = true;
                for (int k = 0; k <= i; k++)
                    if (j == ind[k])
                        valid = false;

                if (!valid) continue;

                if (seg_intersect(origin, p, aux[j].first, aux[j].second))
                    return false;
            }
            origin = p;
            invert_walls(aux, ind[i]);
        }
        else return false;
    }

    for (int i = 0; i < n; i++) {
        bool valid = true;
        for (int j = 0; j < ind.size(); j++)
            if (i == ind[j])
                valid = false;

        if (!valid) continue;

        if (seg_intersect(origin, xhole, aux[i].first, aux[i].second))
            return false;
    }

    return true;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%d %d", &x_1, &y_1);
        hole = point(x_1, y_1);
        origin = point(0, 0);
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d %d", &x_1, &y_1, &x_2, &y_2);
            walls[i] = wall(point(x_1, y_1), point(x_2, y_2));
        }

        int mask = 1 << n, ans = -1;

        bool no_wall = true;
        for (int i = 0; i < n; i++)
            if (seg_intersect(origin, hole, walls[i].first, walls[i].second))
                no_wall = false;

        if (no_wall) ans = 0;

        for (int i = 1; i < mask; i++) {
            vector < int > ind;
            for (int j = 0; j < n; j++)
                if (i & (1 << j))
                    ind.push_back(j);
            sort(ind.begin(), ind.end());

            do {
                if (valid(ind))
                    ans = max(ans, (int)ind.size());
            }
            while (next_permutation(ind.begin(), ind.end()));
        }

        if (ans == -1) printf("impossible\n");
        else printf("%d\n", ans);
    }

    return 0;
}
