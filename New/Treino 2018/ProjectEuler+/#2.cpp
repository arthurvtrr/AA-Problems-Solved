#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t;
ll n, fib[100], acum[100];

int main() {
    fib[1] = fib[2] = 1;
    for (int i = 3; i < 100; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        if (fib[i] % 2 == 0) acum[i] = fib[i];
        acum[i] += acum[i-1];

        if (fib[i] > 40000000000000000LL) break;
    }

    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        for (int i = 82; i > 0; i--)
            if (fib[i] <= n) {
                printf("%lld\n", acum[i]);
                break;
            }
    }
    return 0;
}

