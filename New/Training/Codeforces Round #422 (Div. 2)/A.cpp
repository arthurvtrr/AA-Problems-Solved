#include <bits/stdc++.h>

using namespace std;

long long a, b;

int main() {
    scanf("%d %d", &a, &b);
    long long ans = 1;
    for (long long i = 1; i <= min(a, b); i++)
        ans *= i;
    printf("%lld\n", ans);

    return 0;
}
