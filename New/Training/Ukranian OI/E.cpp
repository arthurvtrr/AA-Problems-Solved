#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

#define AUX 10000

int n, x, y;
long long contx[22000], conty[22000];

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        contx[x+AUX]++;
        conty[y+AUX]++;
    }

    long long sol = 0;
    long long sumx_a = 0, sumx_b = 0, sumx_c = 0;
    long long sumy_a = 0, sumy_b = 0, sumy_c = 0;

    for (int i = -10000; i < 10001; i++) {
        sol += contx[i+AUX] * (i * i * sumx_a - 2LL * i * sumx_b + sumx_c);
        sol += conty[i+AUX] * (i * i * sumy_a - 2LL * i * sumy_b + sumy_c);

        sumx_a += contx[i+AUX];
        sumx_b += i * contx[i+AUX];
        sumx_c += i * i * contx[i+AUX];

        sumy_a += conty[i+AUX];
        sumy_b += i * conty[i+AUX];
        sumy_c += i * i * conty[i+AUX];
    }

    printf("%lld\n", sol);

    return 0;
}
