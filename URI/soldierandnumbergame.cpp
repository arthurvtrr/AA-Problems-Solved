#include <bits/stdc++.h>

using namespace std;

long long fat[5100000], primes[5100000], factor[5100000];

int main() {
    int root = sqrt(5000000);

    for (int i = 2; i <= 5000000; i++)
        factor[i] = i;

    for (int i = 2; i <= root; i++) {
        if (primes[i] == 0)
            for (int j = i*i; j <= 5000000; j += i) {
                primes[j] = 1;
                factor[j] = i;
            }
    }

    for (int i = 2; i <= 5000000; i++)
        fat[i] = fat[i / factor[i]] + 1;

    for (int i = 2; i <= 5000000; i++)
        fat[i] += fat[i-1];

    int t, a, b;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        scanf("%d %d", &a, &b);
        printf("%I64d\n", fat[a] - fat[b]);
    }
    return 0;
}
