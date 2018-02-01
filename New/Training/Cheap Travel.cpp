#include <bits/stdc++.h>

using namespace std;

int n, m, a, b;

int main() {
    scanf("%d %d %d %d", &n, &m, &a, &b);
    if (m*a > b) printf("%d\n", min((n / m) * b + (n % m) * a, (n / m + 1) * b));
    else printf("%d\n", n * a);

    return 0;
}
