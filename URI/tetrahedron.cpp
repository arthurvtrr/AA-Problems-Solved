#include <stdio.h>

using namespace std;

#define mod 1000000007
int main() {
    int n;

    scanf("%d", &n);

    int zD = 1;
    int zABC = 0;
    for (int i = 1; i <= n; i++) {
        int nzD = zABC * 3LL % mod;
        int nzABC = (zABC * 2LL + zD) % mod;
        zD = nzD;
        zABC = nzABC;
    }

    printf("%d\n", zD);

    return 0;
}
