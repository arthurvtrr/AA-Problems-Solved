#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

long long n;

long long gcd(long long a, long long b) { return b == 0? a : gcd(b, a % b); }
long long lcm(long long a, long long b) { return a * (b / gcd(a, b)); }

int main() {
    scanf("%lld", &n);
    if (n == 1) printf("-1\n");
    else printf("%lld %lld %lld\n", n, n+1, lcm(n, n+1));
    return 0;
}
