#include <bits/stdc++.h>

using namespace std;

double a, b, n;

int main() {
    scanf("%lf %lf %lf", &a, &b, &n);
    int ans = round(n / (a / b));
    printf("%d\n", ans);
    return 0;
}
