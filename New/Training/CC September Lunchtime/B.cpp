#include <bits/stdc++.h>

using namespace std;

int q;
unsigned long long n, k, pow2[64];

int main() {
    pow2[0] = 1;
    for (int i = 1; i < 64; i++)
        pow2[i] = 2 * pow2[i-1];

    scanf("%d", &q);

    while (q--) {
        scanf("%llu %llu", &n, &k);

        unsigned long long shift = 0;
        for (int i = 0; i < n-1; i++) {
            if (k % 2 == 1) { k /= 2; shift += pow2[n-i-1]; }
            else k /= 2;
        }

        printf("%llu\n", k + shift);
    }

    return 0;
}

