#include <bits/stdc++.h>

using namespace std;

int n, t, k, d;

int main() {
    scanf("%d %d %d %d", &n, &t, &k, &d);
    int x = (n + k - 1) / k * t;
    int tm = 0;
    while (n > 0) {
        tm++;
        if (tm % t == 0) n -= k;
        if (tm > d && (tm - d) % t == 0) n -= k;
    }

    if (tm < x) printf("YES\n");
    else printf("NO\n");

    return 0;
}
