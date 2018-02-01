#include <bits/stdc++.h>

using namespace std;

int primes[4] = {2, 3, 5, 7};

int main() {
    int x = 1, y;
    for (int i = 0; i < 4; i++) {
        printf("Q %d\n", primes[i]);
        fflush(stdout);
        scanf("%d", &y);
        for (int j = 0; j < y; j++)
            x *= primes[i];
    }
    printf("A %d\n", x);

    return 0;
}
