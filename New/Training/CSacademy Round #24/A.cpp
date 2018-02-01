#include <bits/stdc++.h>

using namespace std;

int n, x;

int main() {
    scanf("%d", &n);
    int ans = 0, atual = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        if (x == 1) atual++;
        else if (atual > 0) atual--;
        ans = max(ans, atual);
    }
    printf("%d\n", ans);

    return 0;
}
