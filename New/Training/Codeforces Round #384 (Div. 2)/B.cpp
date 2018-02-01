#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

long long n, k;

int main() {
    scanf("%lld %lld", &n, &k);

    for (long long i = 0; i < 50; i++) {
        long long mod = 1LL << (i+1);
        if (k % mod == (1LL << i)) {
            printf("%d\n", i+1);
            break;
        }
    }

    return 0;
}
