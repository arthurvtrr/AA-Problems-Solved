#include <bits/stdc++.h>

using namespace std;

#define N 200200
#define PI acos(-1)

int a, b, c, d, n;

struct point {
    int x, y;
} points[N];

bool cmp(point a, point b) {
    return a.x < b.x;
}

int seg[4*N];

void update(int id, int ini, int fim, int pos, int val) {
    if (ini == fim) {
        seg[id] = val;
        return;
    }
    int meio = (ini + fim) / 2;

    if (pos <= meio) update(2*id, ini, meio, pos, val);
    else update(2*id+1, meio+1, fim, pos, val);

    seg[id] = max(seg[2*id], seg[2*id+1]);
}

int query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id];

    int meio = (ini + fim) / 2;

	return max(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

set < int > diff;
map < int, int > ind, posx, posy;
int inv[N];

int main() {
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
        posx[points[i].x] = points[i].y;
        posy[points[i].y] = points[i].x;
        diff.insert(points[i].y);
    }

    int cont = 2;
    for (set < int >::iterator it = diff.begin(); it != diff.end(); it++) {
        inv[cont] = *it;
        ind[*it] = cont++;
    }

    for (int i = 0; i < n; i++)
        points[i].y = ind[points[i].y];

    sort(points, points+n, cmp);

    long double ans = 0.0;

    if (a == c) {
        ans = abs(b - d);
        ans *= 100;

        if (posx.count(a) && posx[a] > min(b, d) && posx[a] < max(b, d)) {
            ans -= 20;
            ans += PI * 10;
        }
    }
    else if (b == d) {
        ans = abs(a - c);
        ans *= 100;

        if (posy.count(b) && posy[b] > min(a, c) && posy[b] < max(a, c)) {
            ans -= 20;
            ans += PI * 10;
        }
    }
    else if ((a-c < 0 && b-d < 0) || (a-c > 0 && b-d > 0)) {
        for (int i = 0; i < n; i++) {
            if (points[i].x < min(a, c) || points[i].x > max(a, c) || inv[points[i].y] < min(b, d) || inv[points[i].y] > max(b, d)) continue;
            int x = query(1, 1, N, 1, points[i].y);
            update(1, 1, N, points[i].y, x+1);
        }

        ans += abs(a - c);
        ans += abs(b - d);
        ans *= 100;
        ans -= 20 * query(1, 1, N, 1, N);
        ans += 10 * (PI / 2) * query(1, 1, N, 1, N);

        if (query(1, 1, N, 1, N) == min(abs(a-c), abs(b-d)) + 1)
            ans += 10 * (PI / 2);
    }
    else {
        for (int i = 0; i < n; i++) {
            if (points[i].x < min(a, c) || points[i].x > max(a, c) || inv[points[i].y] < min(b, d) || inv[points[i].y] > max(b, d)) continue;
            int x = query(1, 1, N, points[i].y, N);
            update(1, 1, N, points[i].y, x+1);
        }

        ans += abs(a - c);
        ans += abs(b - d);
        ans *= 100;
        ans -= 20 * query(1, 1, N, 1, N);
        ans += 10 * (PI / 2) * query(1, 1, N, 1, N);

        if (query(1, 1, N, 1, N) == min(abs(a-c), abs(b-d)) + 1)
            ans += 10 * (PI / 2);
    }

    printf("%.15Lf\n", ans);

    return 0;
}
