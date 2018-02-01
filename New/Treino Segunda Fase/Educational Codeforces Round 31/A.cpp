#include <bits/stdc++.h>

using namespace std;

int n, t, x;

int main() {
    scanf("%d %d", &n, &t);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans++;

        scanf("%d", &x);
        t -= 86400 - x;
        if (t <= 0) break;
    }
    printf("%d\n", ans);

    return 0;
}
