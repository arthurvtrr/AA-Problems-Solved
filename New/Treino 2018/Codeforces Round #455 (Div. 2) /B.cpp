#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    scanf("%d", &n);
    int x = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        x += n-2*i;
        ans = max(ans, x);
    }
    printf("%d\n", ans);

    return 0;
}
