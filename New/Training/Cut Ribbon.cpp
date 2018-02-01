#include <bits/stdc++.h>

using namespace std;

int n, a, b, c;

int main() {
    scanf("%d %d %d %d", &n, &a, &b, &c);

    int ans = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) {
            int x = n - (i*a + j*b);
            if (x >= 0 && x % c == 0)
                ans = max(ans, i + j + x / c);
        }

    printf("%d\n", ans);

    return 0;
}
