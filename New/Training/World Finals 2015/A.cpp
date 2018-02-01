#include <bits/stdc++.h>

using namespace std;

long long p, a, b, c, d, n;
double price[1001000], acum[1001000];

int main() {
    scanf("%lld %lld %lld %lld %lld %lld", &p, &a, &b, &c, &d, &n);
    for (int i = 1; i <= n; i++) {
        price[i] = p * (sin(a * i + b) + cos(c * i + d) + 2);
        acum[i] = max(price[i], acum[i-1]);
    }

    double ans = 0.0;
    for (int i = 2; i <= n; i++)
        ans = max(ans, acum[i-1] - price[i]);
    printf("%.10f\n", ans);

    return 0;
}

