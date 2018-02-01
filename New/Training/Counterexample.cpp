#include <bits/stdc++.h>

using namespace std;

long long l, r;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    scanf("%lld %lld", &l, &r);

    for (long long i = l; i <= r; i++)
        for (long long j = i+1; j <= r; j++)
            for (long long k = j+1; k <= r; k++)
                if (gcd(i, j) == 1 && gcd(j, k) == 1 && gcd(i, k) != 1) {
                    printf("%lld %lld %lld\n", i, j, k);
                    exit(0);
                }
    printf("-1\n");

    return 0;
}
