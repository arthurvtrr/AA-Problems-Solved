#include <bits/stdc++.h>

using namespace std;

int n, m, k;
struct plug {
    int x, y, t, n, p;
} plugs[100100];

bool cmp(plug a, plug b) {
    if (a.t == b.t) {
        if (a.t == 1) return a.x < b.x;
        if (a.t == 2) return a.y < b.y;
        if (a.t == 3) return a.x > b.x;
        return a.y > b.y;
    }
    return a.t < b.t;
}

#define pii pair<int, int>
map < pii, int > cnt;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &plugs[i].x, &plugs[i].y);
        cnt[pii(plugs[i].x, plugs[i].y)]++;
        if (plugs[i].y == 0) {
            plugs[i].t = 1;
            plugs[i].n = n - plugs[i].x;
            plugs[i].p = plugs[i].x;
        }
        else if (plugs[i].x == n) {
            plugs[i].t = 2;
            plugs[i].n = n - plugs[i].y;
            plugs[i].p = plugs[i].y;
        }
        else if (plugs[i].y == n) {
            plugs[i].t = 3;
            plugs[i].n = plugs[i].x;
            plugs[i].p = n - plugs[i].x;
        }
        else {
            plugs[i].t = 4;
            plugs[i].n = plugs[i].y;
            plugs[i].p = n - plugs[i].y;
        }
    }

    sort(plugs, plugs+m, cmp);

    int ans = 1000000000;
    for (int i = 0; i < m; i++) {
        plug a = plugs[i], b = plugs[(i+k-1)%m];
        int x = 0;

        if (a.x == b.x && a.y == b.y && cnt[pii(a.x, a.y)] >= k) x = 0;
        else if (a.x == b.x && a.y == b.y) x = 4*n;
        else if (a.t == b.t && cmp(a, b)) x = abs(a.x - b.x) + abs(a.y - b.y);
        else if (a.t == b.t) x = 4*n - abs(a.x - b.x) - abs(a.y - b.y);
        else {
            if (a.t < b.t) x = max(0, b.t - a.t - 1) * n + a.n + b.p;
            else x = max(0, b.t + 4 - a.t - 1) * n + a.n + b.p;
        }
        ans = min(ans, x);
    }
    printf("%d\n", ans);

    return 0;
}
