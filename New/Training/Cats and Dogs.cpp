#include <bits/stdc++.h>

using namespace std;

int t;
long long c, d, l;

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%lld %lld %lld", &c, &d, &l);
        if (l % 4 != 0 || l < 4 * d + 4 * max(0LL, c - 2 * d) || l > 4 * d + 4 * c) printf("no\n");
        else printf("yes\n");
    }

    return 0;
}
