#include <stdio.h>
#include <math.h>

using namespace std;

int nc, n, k;

int survivor(int n, int k) {
    if (n == 1)
        return 1;
    return (k - 1 + survivor(n-1, k)) % n + 1;
}

int main() {
    scanf("%d", &nc);

    for (int i = 0; i < nc; i++) {
        scanf("%d %d", &n, &k);

        printf("Case %d: %d\n", i+1, survivor(n,k));
    }

    return 0;
}
