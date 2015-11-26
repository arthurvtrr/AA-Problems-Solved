#include <bits/stdc++.h>

using namespace std;

long long ipow(long long base, int exp, int i) {
    long long result = 1;
    while (exp) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
        base %= i;
        result %= i;
    }

    return result;
}

int main() {
    int r;
    scanf("%d", &r);

    int i = pow(2, 31) - 1;

    printf("%lld\n", ipow(3,r,i));
    return 0;
}
