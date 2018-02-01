#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int t, n, m, k;

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d %d %d", &n, &m, &k);

        int sol = 1000000000;

        if (n > m) swap(n, m);
        if (k < n && 2*k + 2 < m)
            sol = min(sol, n / k + ((n % k) > 0));
        if (2*k < n && 3*k + 1 < m)
            sol = min(sol, 5);

        printf("Case #%d: %d\n", tc+1, sol == 1000000000? -1 : sol);
    }
    return 0;
}
