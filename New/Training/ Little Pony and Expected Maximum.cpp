#include <bits/stdc++.h>

using namespace std;

int n, m;

double fastPow(double base, int exp) {
    if (exp <= 0) return 1.0;
    double result = fastPow(base, exp/2);
    result *= result;
    if (exp % 2) result *= base;
    return result;
}

int main() {
    scanf("%d %d", &m, &n);

    double ans = 0.0;
    for (int i = 1; i <= m; i++) {
        double x = i, y = m;
        ans += (fastPow(x / y, n) - fastPow((x-1.0) / y, n)) * x;
    }

    printf("%.12f\n", ans);

    return 0;
}
