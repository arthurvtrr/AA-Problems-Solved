#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

#define MOD 1000000007

int t, n, m, nums[2020];
int fat[104000000];

long long extended_euclid(long long a, long long b, long long &x, long long &y) {
    long long xx = y = 0;
    long long yy = x = 1;
    while (b) {
        long long q = a/b;
        long long t = b; b = a%b; a = t;
        t = xx; xx = x-q*xx; x = t;
        t = yy; yy = y-q*yy; y = t;
    }
    return a;
}

long long invModular(long long a) {
    long long x, y;
    long long d = extended_euclid(a, MOD, x, y);
    if (d > 1) return -1;
    return ((x % MOD) + MOD) % MOD;
}

int main() {
    fat[0] = 1;
    for (int i = 1; i < 104000000; i++) {
        long long aux = i;
        aux *= fat[i-1];
        aux %= MOD;
        fat[i] = (int) aux;
    }

    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        if (n == 1) {
            printf("Case #%d: %d\n", tc+1, m);
            continue;
        }

        long long sol = 0, total = 0;

        for (int i = 0; i < n; i++)
            total += 2 * nums[i] + 1;

        for (int i = 0; i < n; i++)
            for (int j = i+1; j < n; j++) {
                long long x = max(m - total - 1 + nums[i] + nums[j] + 2*n, 0LL);
                long long y = fat[n] * 2 / (n * (n-1));

                long long aux = fat[x], a = fat[n], b = fat[max(x-n, 0LL)];
                aux *= invModular((a * b) % MOD);
                aux %= MOD;
                //printf("%lld\n", aux);
                aux *= y;
                aux %= MOD;
                sol += aux;
                sol %= MOD;
            }

        printf("Case #%d: %lld\n", tc+1, sol);
    }

    return 0;
}
