#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    scanf("%d", &n);
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, 2*i + 2*(n/i) + (n % i? 2 : 0));
    }
    printf("%d\n", ans);

    return 0;
}
