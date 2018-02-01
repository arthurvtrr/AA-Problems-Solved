#include <bits/stdc++.h>

using namespace std;

int r, d, n;

struct circle {
    int x, y, r;
} cs[100100];

int main() {
    scanf("%d %d %d", &r, &d, &n);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &cs[i].x, &cs[i].y, &cs[i].r);
        if (cs[i].x*cs[i].x + cs[i].y*cs[i].y >= (r - d + cs[i].r)*(r - d + cs[i].r))
            if (cs[i].x*cs[i].x + cs[i].y*cs[i].y <= (r - cs[i].r)*(r - cs[i].r))
                ans++;
    }

    printf("%d\n", ans);

    return 0;
}

