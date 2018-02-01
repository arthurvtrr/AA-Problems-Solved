#include <bits/stdc++.h>

using namespace std;

int n, t, q, a, b, spec[1010];

struct point {
    int x, y;
} points[1010];

int nxt[1010];

int dist(int x, int y) {
    return abs(points[x].x - points[y].x) + abs(points[x].y - points[y].y);
}

int main() {
    scanf("%d %d", &n, &t);
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", &spec[i], &points[i].x, &points[i].y);

    for (int i = 1; i <= n; i++)
        nxt[i] = spec[i]? i : 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j && spec[j]) {
                if (nxt[i] == 0) nxt[i] = j;
                else if (dist(i, j) < dist(i, nxt[i])) nxt[i] = j;
            }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &a, &b);
        printf("%d\n", min(dist(a, b), dist(a, nxt[a]) + t + dist(b, nxt[b])));
    }

    return 0;
}

