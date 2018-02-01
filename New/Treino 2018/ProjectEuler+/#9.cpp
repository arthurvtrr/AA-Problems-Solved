#include <bits/stdc++.h>

using namespace std;

int t, n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int ans = -1;
        for (int a = 1; a < n; a++) {
            if ((n*n - 2*a*n) % (2*n - 2*a)) continue;

            int b = (n*n - 2*a*n) / (2*n - 2*a);
            int c = sqrt(a*a + b*b);
            if (c*c != a*a + b*b) continue;

            if (a < b && b < c && a + b + c == n) ans = max(ans, a*b*c);
        }
        printf("%d\n", ans);
    }
    return 0;
}

