#include <bits/stdc++.h>

using namespace std;

long long n, a, b, c, d;

int main() {
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &n);
    long long ans = 0;
    if (n >= 2 && d < 8*a && d < 4*b && d < 2*c) {
        ans += (n / 2) * d;
        n %= 2;
    }
    if (c < 4*a && c < 2*b) ans += n * c;
    else if (b < 2*a) ans += n * b * 2;
    else ans += n * a * 4;

    printf("%lld\n", ans);

    return 0;
}
