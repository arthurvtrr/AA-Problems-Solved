#include <bits/stdc++.h>

using namespace std;

int n, x, y;

int main() {
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++) {
        scanf("%d", &y);
        x -= y;
    }
    if (x != n-1) printf("NO\n");
    else printf("YES\n");

    return 0;
}

