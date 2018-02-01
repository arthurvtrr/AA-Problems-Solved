#include <bits/stdc++.h>

using namespace std;

int n, s[200200], g[200200], maxi[200200];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &s[i], &g[i]);
        maxi[i] = s[i] + g[i];
    }

    for (int i = 1; i < n; i++)
        maxi[i] = min(maxi[i], maxi[i-1] + 1);
    for (int i = n-2; i >= 0; i--)
        maxi[i] = min(maxi[i], maxi[i+1] + 1);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (maxi[i] < s[i]) {
            printf("-1\n");
            return 0;
        }
        ans += maxi[i] - s[i];
    }
    printf("%lld\n", ans);
    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", maxi[i]);
    }
    printf("\n");

    return 0;
}
